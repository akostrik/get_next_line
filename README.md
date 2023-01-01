# get_next_line

A project of 42 School

Solo, about 70 hours

How to run:

```$ make```

--------------------------

Tester https://github.com/Tripouille/gnlTester

[Mandatory]

[BUFFER_SIZE = 1]: 

Invalid fd: 1.OK 2.OK 3.OK 

files/empty: 1.OK 2.OK 

files/nl: 1.OK 2.OK 

files/41_no_nl: 1.OK 2.OK 

files/41_with_nl: 1.OK 2.OK 3.OK 

files/42_no_nl: 1.OK 2.OK 

files/42_with_nl: 1.OK 2.OK 3.OK 

files/43_no_nl: 1.OK 2.OK 

files/43_with_nl: 1.OK 2.OK 3.OK 

files/multiple_nlx5: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/alternate_line_nl_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/alternate_line_nl_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/big_line_no_nl: 1.OK 2.OK 

files/big_line_with_nl: 1.OK 2.OK 

stdin: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

[BUFFER_SIZE = 42]: 

Invalid fd: 1.OK 2.OK 3.OK 

files/empty: 1.OK 2.OK 

files/nl: 1.OK 2.OK 

files/41_no_nl: 1.OK 2.OK 

files/41_with_nl: 1.OK 2.OK 3.OK 

files/42_no_nl: 1.OK 2.OK 

files/42_with_nl: 1.OK 2.OK 3.OK 

files/43_no_nl: 1.OK 2.OK 

files/43_with_nl: 1.OK 2.OK 3.OK 

files/multiple_nlx5: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/alternate_line_nl_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/alternate_line_nl_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/big_line_no_nl: 1.OK 2.OK 

files/big_line_with_nl: 1.OK 2.OK 

stdin: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

[BUFFER_SIZE = 10000000]: 

Invalid fd: 1.OK 2.OK 3.OK 

files/empty: 1.OK 2.OK 

files/nl: 1.OK 2.OK 

files/41_no_nl: 1.OK 2.OK 

files/41_with_nl: 1.OK 2.OK 3.OK 

files/42_no_nl: 1.OK 2.OK 

files/42_with_nl: 1.OK 2.OK 3.OK 

files/43_no_nl: 1.OK 2.OK 

files/43_with_nl: 1.OK 2.OK 3.OK 

files/multiple_nlx5: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/multiple_line_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 

files/alternate_line_nl_no_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/alternate_line_nl_with_nl: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

files/big_line_no_nl: 1.OK 2.OK 

files/big_line_with_nl: 1.OK 2.OK 

stdin: 1.OK 2.OK 3.OK 4.OK 5.OK 6.OK 7.OK 8.OK 9.OK 10.OK 

--------------------------
	
Moulinette : You have been graded 100 on getnextline:

basic_tests: GNL OK | bonus_tests: Compilation failed
