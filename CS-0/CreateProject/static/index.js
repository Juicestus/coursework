/*
 * static/js/index.js
 * 
 * 2021 CSP Create Project
 * A realtime internet chat room using WebSockets handled with Flask SocketIO
 * Built on a Flask Python server with a JavaScript client
 */

/*
 * Procedure scrollDown 
 * Scrolls down the table of messages using a
 * fun little animation
 */

function scrollDown() 
{
    $('table.msgtable').animate(
    {
        scrollTop: $('table.msgtable')[0].scrollHeight
    }, 500);
};


/*
* This procedure shows the list being used 
* 
* Procedure for displaying messages 
* Takes paramter of message array from server
* Iterates through messages and renders them
* on the HTML page
*/

function displayMessages(servedMessages)
{
    // Get messages as array from server input
    var messages = Array.from(servedMessages);     

    var table = '';
    // For each message in messages    
    for (var i=0; i < messages.length; i++) 
    {
        // Adds HTML for each message
        message = messages[i];
        table += `<tr><td class="username">${message.username}</td>`;
        table += `<td class="msg">${message.msg}</td>`;
        table += `<td class="time">${message.time}</td></tr>`;
    }

    table += '</table>'; 
    // Render table in document
    document.getElementById('messages').innerHTML = table; 
}


var lastSent = 0; // The time since last sent message (UNIX timestamp)
const sendDelay = 3;    // Delay between sends in seconds

// On page load
$(document).ready(function() 
{
    scrollDown();         // Scroll down messages on document load
    var socket = io();    // Inst Socket IO connection

    // On socket connection
    socket.on('connect',function()    
    { 
        // Calls for initial messages
        socket.emit('connected') 

        /*
         * On form being submitted
         * Checks for valid username
         * Checks for valid message
         * Checks if user waited since last send
         * If all checks are correct, formats the 
         * message dictionary and sends the socket
        */
        var form = $('form').on('submit',function(f) 
        { 
            f.preventDefault(); // Prevent default action
            var time = (new Date).getTime();    // Get the current time as UNIX timestamp
            if (time > lastSent + (sendDelay * 1000)) // Looks to see if its been longer than the delay since last send
            {    
                var username = $('input.username').val();    // Sets username to username box
                var msg = document.getElementById('messageArea').value // Sets message to message box
                if (!msg.replace(/\s/g, '').length) // Check if there are all spaces etc.
                { 
                    alert('Message does not contain any characters worth sending!');    
                } else {
                    if (!username.replace(/\s/g, '').length) 
                    {    
                        alert('Must provide username!')        
                    } else {
                        socket.emit('updateMessage',{    
                            username: username,
                            msg: msg,
                            time: time
                        });

                        lastSent = time;    
                        document.getElementById('msbox').value = '';
                        $('#msbox').val('');
                        $('input.message').val('').focus();     
                    }
                }
            }
        });    
    });

    /*
     * This action is performed when messages are 
     * sent from the server. They are inputed as
     * the parameter serverdMessages
     */

    socket.on('newMessage', function(servedMessages)
    {
        // Display the messages on the HTML Page
        // Calls student made procedure
        displayMessages(servedMessages);

        // Scroll down to newest message
        // Calls student made procedure
        scrollDown(); 
    });
});