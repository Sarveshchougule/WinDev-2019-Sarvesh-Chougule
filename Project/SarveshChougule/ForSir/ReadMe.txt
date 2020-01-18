Welcome To SKC World !!!!

My Name is Sarvesh Chougule....
Of WINRT 2019 Batch and 
Of WM_CLOSE Group ....

# Rename this file to there original Name....
1.For Server Side :-

	ReadWriteServerWithRegFile.abc1		=>   ReadWriteServerWithRegFile.dll

2.For Registry :-

	RegistryServer.abc2			=>   RegistryServer.reg

3.For Client Side :-

	ExperimentationNo2.abc			=>   ExperimentationNo2.exe
	

#Before running project :-
 
Run the Registry of x32 bit Registry and only x32 Bit Release or x32 Bit Debug, move server dll to "C:\Windows\SysWOW64\" location .... then you run Client exe .....

Sorry for x64 bit Client is not ready..... But x32 bit will work as fine in any windows operating system.....


#Here is a Key of My Project :- 			(You Can Read If you May....)


First Launch a exe then "space to proceed", Then a dialogue box will appear and choose your option as your wish. Suppose you choose "Data Entry" then a data entry dialogue
box will appear. Enter all the entries and if you won't enter any specific entry then it will show a error messagebox. Case sensitivity of entries is not necessary, Only be
care full about the age which should be a "Numeric Value Only" and for date, month and year which is more case sensitive, example (it will detect leap year as well as last 
day of February of that leap year or not...) as well as year should not be greater then "2020" (<strickly>) same goes for month which should less then equal to "12" (<strickly>) 
but for the date it depend month wise and leap year wise... Date, Month and Year Column should contain "Numeric Value Only". Salary Column should also be enter a "Numeric Value Only" 
(<strickly>)....

Gender and Maritial Status are already decided so it won't matter for error purpose ....

If All data is filled then click only "once" at "Add Entry"Button, if you Click("Add Entry"Button) multiple times then it will add same entry multiple times, so click 
Once only (<Strickly>), After Clicking "Add Entry Once" checking MessageBox will appear so just "Ok" them.... Then you can choose "Display" Button which will show Traversing 
of Records.... Or other wise you can choose Cancel button it will go back to menu ....  And In Menu if you click Cancel button then it will "Exit from your EXE"....

If You are at Menu and choose "Read\Search Records" then it will show Traversing of Records with no entries at all because file is empty....

But After Adding Multiple entries you can see Multiple Records or data entries in "Read\Search Records"..... You Can also search Any Name that is displayed below with other 
entries, if it hit match then you will get specific output .... or else (if it doesn't hit match then) you will get error MessageBox saying "there is no entry exist with this Name"...
While searching By Name if you didn't enter any entry then it will give error saying this "SearchBox is empty".... Searching is done for Name Only(<strickly>).....
And also while clicking "Search Button" click Once only (<strickly>).... 

If You click "Display All" button then all entries will be display after the search ..... If you click "cancel" button then it will go back to "Menu" ......