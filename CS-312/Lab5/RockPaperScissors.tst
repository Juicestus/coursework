load RockPaperScissors.hdl,
compare-to RockPaperScissors.cmp,
output-file RockPaperScissors.out,
output-list A%B3.2.3 B%B3.2.3 out%B3.2.3;


set A %B00,
set B %B00,
eval,
output;

set A %B00,
set B %B01,
eval,
output;

set A %B00,
set B %B10,
eval,
output;



set A %B01,
set B %B00,
eval,
output;

set A %B01,
set B %B01,
eval,
output;

set A %B01,
set B %B10,
eval,
output;


set A %B10,
set B %B00,
eval,
output;

set A %B10,
set B %B01,
eval,
output;

set A %B10,
set B %B10,
eval,
output;