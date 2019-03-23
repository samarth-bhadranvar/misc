#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <list>

using namespace std;

class file
{


public:
char* perm ;
//string perm;
int links;
int uid;
int gid;
int size;
char* time;
// char* name;
string name;

bool operator <(const file & fileObject) const
	{
		return size < fileObject.size;
	}



// string printr()
// {
// return perm+" "+links+" "+uid+" "+gid+" "+size+" "+time+" "+name+"\n";
// }

};

struct fileComparator
{
	bool operator ()(const file & file1, const file & file2)
	{
		if(file1.name == file2.name)
			return file1 < file2;
		return file1.name < file2.name;
 
	}
};

void strmode(mode_t mode, char * buf) {
  const char chars[] = "rwxrwxrwx";
  for (size_t i = 0; i < 9; i++) {
    buf[i] = (mode & (1 << (8-i))) ? chars[i] : '-';
  }
  buf[9] = '\0';
}


int main()

{

//system("ls -l");


DIR* dir;
struct dirent* ptr;
struct stat buf;
struct tm* time;
char timebuffer [100];
char permissions[10];

dir= opendir("/home/cs104/cpp");

list<file> fileList;

while((ptr = readdir(dir))!=NULL)
{

// -rwxrwxr-x 1 cs104 cs104 24640 Mar 19 18:33 a.out


stat(ptr->d_name,&buf);

time=localtime(&buf.st_mtime);

strftime(timebuffer,100,"%b %y %R",time);

strmode(buf.st_mode,permissions);

file finfo;
finfo.perm=permissions;
finfo.links=buf.st_nlink;
finfo.uid=buf.st_uid;
finfo.gid=buf.st_gid;
finfo.size=buf.st_size;
finfo.time=timebuffer;
finfo.name=ptr->d_name;

fileList.push_back(finfo);



//cout<<permissions<<" "<<buf.st_nlink<<" "<<buf.st_uid<<" "<<buf.st_gid<<" "<<buf.st_size<<" "<<timebuffer<<" "<<ptr->d_name<<"\n";

}


// fileList.sort();


fileList.sort(fileComparator());
 



for (list<file>::iterator it = fileList.begin(); it != fileList.end(); ++it){
	//cout << it->size;
	cout<<it->perm<<" "<<it->links<<" "<<it->uid<<" "<<it->gid<<" "<<it->size<<" "<<it->time<<" "<<it->name<<"\n";
}


return 0;

}


