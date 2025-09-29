/*
	Original author of the starter code
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date: 2/8/20
	
	Please include your Name, UIN, and the date below
	Name:	Justus Languell
	UIN:	135007144
	Date:	Sep 28 2025
*/
#include "common.h"
#include "FIFORequestChannel.h"
#include "sys/wait.h"

using namespace std;


int main (int argc, char *argv[]) {
	int opt;
	int p = -1;
	double t = -1.0;
	int e = 1;
	string filename = "";
	int bufcap = MAX_MESSAGE;
	bool make_new_chan = false;

	while ((opt = getopt(argc, argv, "p:t:e:f:m:c")) != -1) {
		switch (opt) {
			case 'p':
				p = atoi(optarg);
				break;
			case 't':
				t = atof(optarg);
				break;
			case 'e':
				e = atoi(optarg);
				break;
			case 'f':
				filename = optarg;
				break;
			case 'm':
				bufcap = atoi(optarg);
				break;
			case 'c':
				make_new_chan = true;
				break;
		}
	}

	// Start the server as a child proc
	pid_t pid;
	if ((pid  = fork()) == 0)
	{
		char* args[4] = { (char*)"./server", (char*)"-m", 
				(char*)std::to_string(bufcap).c_str(), NULL };
		execvp(args[0], args);
		perror("Starting the server as a child proc has failed\n");
		exit(1);
	}	
	
    FIFORequestChannel base_chan("control", FIFORequestChannel::CLIENT_SIDE);
	FIFORequestChannel* chan = &base_chan;

	if (make_new_chan)
	{
		MESSAGE_TYPE nc = NEWCHANNEL_MSG;
		chan->cwrite(&nc, sizeof(nc));
		char newcname[256];
		chan->cread(newcname, sizeof(newcname));
		chan = new FIFORequestChannel(newcname, FIFORequestChannel::CLIENT_SIDE);
	}

#ifdef CHANNEL_EXAMPLE		
	#warning "Are you sure you want to run this example code?"
    char buf[MAX_MESSAGE]; // 256
    datamsg x(1, 0.0, 1);
	
	memcpy(buf, &x, sizeof(datamsg));
	chan->cwrite(buf, sizeof(datamsg)); // question
	double reply;
	chan->cread(&reply, sizeof(double)); //answer
	cout << "For person " << p << ", at time " << t << ", the value of ecg " << e << " is " << reply << endl;
	
    // sending a non-sense message, you need to change this
	filemsg fm(0, 0);
	string fname = "teslkansdlkjflasjdf.dat";
	
	int len = sizeof(filemsg) + (fname.size() + 1);
	char* buf2 = new char[len];
	memcpy(buf2, &fm, sizeof(filemsg));
	strcpy(buf2 + sizeof(filemsg), fname.c_str());
	chan->cwrite(buf2, len);  // I want the file length;

	delete[] buf2;
#endif
	printf("Query:	p = %d t = %f e = %d f = \"%s\"\n", p, t, e, filename.c_str());

	/*
	 * File transfer (this one first for simplicity).
	 */
	if (filename != "")
	{
		char* buf = new char[bufcap];	

		// Send a frame that requests the file size
		filemsg fm(0, 0);
		int len = sizeof(fm) + filename.size() + 1;

		// pack fm obj
		memcpy(buf, &fm, sizeof(fm));
		// pack fn
		strcpy(buf + sizeof(fm), filename.c_str());
		chan->cwrite(buf, len);
		// grab the resp (size)
		int64_t fsize;
		chan->cread(&fsize, sizeof(fsize));

		// prepare output file
		ofstream of;
		of.open("received/" + filename, ios::binary);
		
		// process the transfer
		int64_t offset = 0;
		while (offset < fsize)
		{
			int chunk_sz = min(bufcap, (int)(fsize - offset));
			filemsg fm(offset, chunk_sz);
			memcpy(buf, &fm, sizeof(fm));
			strcpy(buf + sizeof(fm), filename.c_str());
			chan->cwrite(buf, len);	//todo? this len change? no right
			chan->cread(buf, chunk_sz);
			of.write(buf, chunk_sz);
			offset += chunk_sz;
		}
		delete[] buf;
	}

	/*
	 * Single data pt. query.
	 */
	else if (p != -1 && t >= 0 && e != -1)
	{
		datamsg d(p, t, e);
		chan->cwrite(&d, sizeof(d));

		double resp;
		chan->cread(&resp, sizeof(resp));
		
		cout << "For person " << p << ", at time " << t << ", the value of ecg " << e << " is " << resp << endl;
	}
	/*
	 * Requesting 1000 data pts.
	 */
	else if (p != -1)
	{
		ofstream of;
		of.open("received/x1.csv");
		for (int i = 0; i < 1000; i++)
		{
			double t = i * 0.004;

			datamsg d1(p, t, 1);
			datamsg d2(p, t, 2);
			double r1, r2;

			chan->cwrite(&d1, sizeof(d1));
			chan->cread(&r1, sizeof(r1));

			chan->cwrite(&d2, sizeof(d2));
			chan->cread(&r2, sizeof(r2));

			of << t << "," << r1 << "," << r2 << "\n";
			//cout << t << "," << r1 << "," << r2 << "\n";
		}
		of.close();
	}
	
    MESSAGE_TYPE m = QUIT_MSG;
    base_chan.cwrite(&m, sizeof(MESSAGE_TYPE));
	if (make_new_chan)
	{
    	chan->cwrite(&m, sizeof(MESSAGE_TYPE));
		delete chan;
	}
	wait(NULL);		
}



















