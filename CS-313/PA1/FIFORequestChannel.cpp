#include "FIFORequestChannel.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/*		CONSTRUCTOR/DESTRUCTOR FOR CLASS	R e q u e s t C h a n n e l		*/
/*--------------------------------------------------------------------------*/

FIFORequestChannel::FIFORequestChannel (const string _name, const Side _side) : my_name( _name), my_side(_side) {
	pipe1 = "fifo_" + my_name + "1";
	pipe2 = "fifo_" + my_name + "2";
		
	if (_side == SERVER_SIDE) {
		wfd = open_pipe(pipe1, O_WRONLY);
		rfd = open_pipe(pipe2, O_RDONLY);
	}
	else {
		rfd = open_pipe(pipe1, O_RDONLY);
		wfd = open_pipe(pipe2, O_WRONLY);
	}
}

FIFORequestChannel::~FIFORequestChannel () { 
	close(wfd);
	close(rfd);

	remove(pipe1.c_str());
	remove(pipe2.c_str());
}

/*--------------------------------------------------------------------------*/
/*			MEMBER FUNCTIONS FOR CLASS	R e q u e s t C h a n n e l			*/
/*--------------------------------------------------------------------------*/

int FIFORequestChannel::open_pipe (string _pipe_name, int mode) {
	mkfifo (_pipe_name.c_str (), 0600);
	int fd = open(_pipe_name.c_str(), mode);
	if (fd < 0) {
		EXITONERROR(_pipe_name);
	}
	return fd;
}

int FIFORequestChannel::cread (void* msgbuf, int msgsize) {
	return read (rfd, msgbuf, msgsize); 
}

int FIFORequestChannel::cwrite (void* msgbuf, int msgsize) {
	return write (wfd, msgbuf, msgsize);
}

string FIFORequestChannel::name () {
	return my_name;
}
