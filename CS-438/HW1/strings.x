/* strings.x - demonstration of working with strings via rpc */

struct stuff {
	string name<64>;
	int val;
};

program TEST_PROG {
	version TEST_VERS {
		string TEST_FUNC(stuff)  = 1;	/* procedure number = 1 */
	} = 1;
} = 100500;	/* replace 88888 with some random numbers */
