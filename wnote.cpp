/*
* Brock DEV
* See LICENSE file.
*
* Developed by
* Brock DEV (https://github.com/BrockDeveloper).
* WebSite: https://brockdev.it
*
* This source code is distributed under the CC BY-NC-SA 4.0 license:
* https://creativecommons.org/licenses/by-nc-sa/4.0/
* you are FREE to SHARE and ADAPT UNDER THE FOLLOWING TERMS:
* 
* ATTRIBUTION You must give appropriate credit, provide a link to the
* license, and indicate if changes were made.
*
* NON COMMERCIAL You may not use the material for commercial purposes.
*
* SHARE ALIKE If you remix, transform, or build upon the material, you
* must distribute your contributions under the same license as the original.
*
*
* This source code is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY.
*/

#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <fstream>
#include <windows.h>
#include <direct.h>
#include <stdexcept>
#pragma comment(lib, "shell32.lib")
using namespace std;

const string EXT=".note";             //note file extension
const string ALL_EXT="*"+EXT;         //all note files
const string MAIN_PATH="\\note\\";    //notes folder path

string get_doc_path();                        //get the default user documents folder path (Windows OS)
void copy_clipboard(const string & );         //copy string to clipboard
string get_file_name(WIN32_FIND_DATA );       //get the file name from Windows data file

int main(int argc,char* argv[])
{
	//no arguments: displays help command
	if(argc==1)
	{
		//displays help command
		cout<<"Creates new note:       note -n <name> -c <note content>"<<endl;
		cout<<"Displays a saved note:  note -v <name>"<<endl;
		cout<<"Copy a saved note:      note -c <name>"<<endl;
		cout<<"Removes a saved note:   note -r <name>"<<endl;
		cout<<"Lists all notes:        note -l"<<endl;
		cout<<"Setup notes folder:     note -s"<<endl;
		
		//exit the program
		return 0;
	}
	else
	{
		//get the first argument
		string param=argv[1];
		
		//get the notes folder directory
		string notes_path = get_doc_path() + MAIN_PATH;
		if(notes_path.empty())
		{
			cout<<"Error in reaching the notes";
			return 0;
		}
		
		//setup notes folder
		if(param=="-s")
		{
			int status = _mkdir(notes_path.c_str());
			if ((status < 0) && (errno != EEXIST))
			{
				cout<<"Error in creating the notes folder";
				return 0;	
			}
			else
			{
				cout<<"Notes folder created";
			}
		}
		
		//creates a new note
		if(param=="-n")
		{
			string note_name;
			string snd_param;
			try
			{
				//file name with correct extension
				note_name=argv[2];
				note_name+=EXT;
				
				//get the second parameter
				snd_param=argv[3];
			}
			catch(logic_error& e)
			{
    			return 0;
			}
			
			//if the content is specified
			if(snd_param=="-c")
			{
				//create the note file in writing mode
				fstream note_file((notes_path+note_name).c_str(),ios::out);
				
				//write the note content into the note file
				for(int i=4;i<argc;i++)
					note_file<<argv[i]<<" ";
					
				//update the user
				cout<<"Note created";
					
				//close the note file
				note_file.close();
			}
		}
		
		//view a saved note
		if(param=="-v")
		{
			//reader buffer
			string buffer;
			
			//file name with correct extension
			string note_name;
			try
			{
				note_name=argv[2];
				note_name+=EXT;
			}
			catch(logic_error& e)
			{
    			return 0;
			}
			
			//open the note file in read in reading mode
			fstream note_file((notes_path+note_name).c_str(),ios::in);
			
			//check if the note exists
			if(!note_file)
			{
				cout<<"No note with this name.";
				note_file.close();
			}
			else
			{
				//read the note file
				getline(note_file,buffer);
				cout<<buffer;
				
				//close the note file
				note_file.close();
			}
		}
		
		//copy note to clipboard
		if(param=="-c")
		{
			//reader buffer
			string buffer;
			
			//file name with correct extension
			string note_name;
			try
			{
				note_name=argv[2];
				note_name+=EXT;
			}
			catch(logic_error& e)
			{
    			return 0;
			}
			
			//open the note file in read in reading mode
			fstream note_file((notes_path+note_name).c_str(),ios::in);
			
			//check if the note exists
			if(!note_file)
			{
				cout<<"No note with this name.";
				note_file.close();
			}
			else
			{
				//read the note file
				getline(note_file,buffer);
				
				//copy to clipboard
				copy_clipboard(buffer);
				
				//update the user
				cout<<"Copied to clipboard.";
				
				//close the note file
				note_file.close();
			}
		}
		
		//remove a saved note
		if(param=="-r")
		{
			//file name with correct extension
			string note_name;
			try
			{
				note_name=argv[2];
				note_name+=EXT;
			}
			catch(logic_error& e)
			{
    			return 0;
			}
			
			//try to delete the note file and notifies the user of the result of the request
			int result = remove((notes_path+note_name).c_str());
			if( result == 0 )
			    cout<<"Note deleted.";
			else 
			    cout<<"Can't delete the note.";
		}
		
		//view all saved notes name
		if(param=="-l")
		{
			//Windows find data
			WIN32_FIND_DATA file_data;
			
			//searchs all notes file
			HANDLE hSearch;
			hSearch=FindFirstFile(TEXT((notes_path+ALL_EXT).c_str()),&file_data);
			
			//if there ar no notes present
			if(hSearch==INVALID_HANDLE_VALUE)
			{
				cout<<"There are no notes present.";
				return 0;
			}
			
			//displays all notes name
			cout<<endl<<"- "<<get_file_name(file_data)<<endl;
			while(FindNextFile(hSearch,&file_data))
			{
				cout<<"- "<<get_file_name(file_data)<<endl;
			}
				
			FindClose(hSearch);
		}
	}
}

//get the default user documents folder path (Windows OS)
string get_doc_path()
{
	//search user default documents folder
	CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	//check the result
    if (result != S_OK)
        return "";
    else
        return string(my_documents);
}

//copy string to clipboard
void copy_clipboard(const string &s)
{
	OpenClipboard(0);
	EmptyClipboard();	
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

//get the file name from Windows data file
string get_file_name(WIN32_FIND_DATA file_data)
{
	//get the file name from data file
	string file_name=file_data.cFileName;
	
	//remove the extension
	int index=file_name.find(EXT);
	file_name=file_name.substr(0,index);
	
	//return the file name
	return file_name;
}

