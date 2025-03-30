/*
Given a time in -hour AM/PM format, convert it to military (24-hour) time.

Note: - 12:00:00AM on a 12-hour clock is 00:00:00 on a 24-hour clock.
- 12:00:00PM on a 12-hour clock is 12:00:00 on a 24-hour clock.

Example


Return '12:01:00'.


Return '00:01:00'.

Function Description

Complete the timeConversion function in the editor below. It should return a new string representing the input time in 24 hour format.

timeConversion has the following parameter(s):

string s: a time in  hour format
Returns

string: the time in  hour format
Input Format

A single string  that represents a time in -hour clock format (i.e.:  or ).

Constraints

All input times are valid
Sample Input

07:05:45PM
Sample Output

19:05:45
*/

string timeConversion(string s) {

// firstly we need to check if it is AM or PM
// we could potentially introduce a hash table (unordered_map) where as
// key we have the PM and AM and how this is mapped to 24 hour

unordered_map<string, string> map12_to_24_pm = {
{"12","12"},
{"01" , "13"},
{"02" , "14"},
{"03" , "15"},
{"04" , "16"},
{"05" , "17"},
{"06" , "18"},
{"07" , "19"},
{"08" , "20"},
{"09" , "21"},
{"10" , "22"},
{"11" , "23"},
};

// retrieve only hte useful info
string am_or_pm = s.substr(8,10);
string hour = s.substr(0,2);
cout<<hour<<endl;

if (am_or_pm == "PM" ){
    s.replace(0,2,map12_to_24_pm[s.substr(0,2)]);
}

if (am_or_pm == "AM" && hour == "12" ){
    s.replace(0,2,"00");
}
return (s.substr(0,8));

}