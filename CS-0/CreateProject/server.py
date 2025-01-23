#!/usr/bin/env python3
# server.py

# 2021 CSP Create Project
# A realtime internet chat room using WebSockets handled with Flask SocketIO
# Built on a Flask Python server with a JavaScript client

# Libraries Flask and Flask SocketIO must be installed using PIP, the Python Package Manager
# This project is designed to be ran on a UNIX system, tested on MacOS 11 and Ubuntu 18.04 LTS

# Flask <https://flask.palletsprojects.com/en/1.1.x/>
# Flask SocketIO <https://flask-socketio.readthedocs.io/en/latest/>

from flask import Flask, render_template, url_for   # Flask handles hosting of webserver   
                                                    # install with: pip install flask                    
from flask_socketio import SocketIO, emit           # Flask SocketIO handles WebSocket Interface              
                                                    # install with: pip install flask_socketio
from datetime import datetime                       # Datetime handles dates and times                         
                                                    # preinstalled

# Setup Socket Enviorment with App
app = Flask(__name__) 
socketio = SocketIO(app) 


# Procedure makeSafe 
# Parameter unsafeText is the text from the user
# Returns safeText, the safe unsafeText
# Iterates through string of text to search and replace characters
# <  : &lt;
# >  : &gt;
# \n : <br>

def makeSafe(unsafeText):
    safeText = str()

    # Sequencing and iteration (through string)
    for i in range(len(unsafeText)):
        char = unsafeText[i]

        # Selection
        if char == '<':
            safeText += '&lt;'
        elif char == '>':
            safeText += '&gt;'
        elif char == '\n':
            safeText += '<br>'
        else:
            safeText += char

    return safeText


# Instantiate list of messages
messages = list() 

# Socket input event
# Message comes in from client (the parameter message)
# Parameter message is a dictionary containing username, message, and time

@socketio.event                                 
def updateMessage(message):                         

    # Time is converted from UNIX timestamp epoch into human readable format
    message['time'] = datetime.utcfromtimestamp(int(message['time']) / 1000)
    message['time'] = message['time'].strftime('%m / %d<br>%Y<br>%H:%M:%S') 

    # Calls makeSafe procedure to prevent users from rendering their own HTML 
    message['username'] = makeSafe(message['username'])
    message['msg'] = makeSafe(message['msg'])

    # Appends message to list of messages
    messages.append(message)

    # List of messages is sent to all the clients to be updated
    emit('newMessage', messages, broadcast=True)   


# On client connection send current messages list to client
# as they just joined and need to see the messages without waiting
# for someone to send

@socketio.event                                 
def connected():                                
    
    # List of messages is sent to all the clients to be updated
    emit('newMessage', messages, broadcast=True)   


# Using flask, serve index.html page to the client
@app.route('/')                                 
def index():            
    return render_template('index.html')         


# ENTRY POINT
if __name__ == '__main__':
    # Run SocketIO App and Async subprocesses in debug mode
    socketio.run(app, debug=True)         
