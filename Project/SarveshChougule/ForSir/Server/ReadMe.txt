Welcome to skc world ....

Be careFull with Registry File's ....
OR Otherwise Your Registry file system will get corrupted and will have to reinstall the windows OS...

For Server Side :-

Debug and Release folder inside the ReadWriteServerWithRegFile are x32 bit file's which contain's ReadWriteServerWithRegFile.dll should be copied to C:\Windows\SysWOW64\  ....
x64\Debug and x64\Release folder inside the ReadWriteServerWithRegFile are x64 bit file's which contain's ReadWriteServerWithRegFile.dll should be copied to C:\Windows\System32\  ....


Similary,

For Client Side :-
	Contain's
		1. Debug and Release which has x32 bit .exe 
		2. x64\Debug and x64\Release has x64 bit .exe 