#include<iostream>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
class inodes {
public:
	char name[8];
	int size;
	int blockpointer[8];
	int used;
	inodes() {
		used = 0;
		size = 0;
		memset(name, 0, 8);
		for (int i = 0; i < 8; i++)
		{
			blockpointer[i] = -1;
		}
	}
	void useinode(char* name, vector<int> &arr) {
		for (int i = 0; i < 8; i++)
		{
			this->name[i] = name[i];
		}
		int index = 0;
		for (int i = 0; i < 8; i++)
		{

			if (blockpointer[i] == -1 && index < arr.size())
			{
				blockpointer[i] = arr[index];
				index++;
			}
		}
		size += arr.size();
	}
};
class superblock {
public:
	bool arr[128];
	vector<inodes> in;

	superblock() {
		arr[0] = true;
		for (int i = 0; i < 127; i++)
		{
			arr[i] = false;
		}
		for (int i = 0; i < 16; i++)
		{
			inodes in1;
			in.push_back(in1);
		}
	}
	vector<int> findfreeblocks(int size)
	{
		vector<int> v1;
		int count_free = 0;
		for (int i = 0; i < 128; i++)
		{
			if (arr[i] == false && count_free < size)
			{
				v1.push_back(i);
				count_free++;
			}
		}
		if (count_free < size)
		{
			v1.resize(0);
			return v1;
		}
		return v1;
	}
	void set_file(vector<int> v, char* name)
	{
		for (int i = 0; i < 16; i++)
		{
			if (in[i].used == 0)
			{
				in[i].used = 1;
				for (int j = 0; j < v.size(); j++) {
					arr[v[j]] = true;
				}
				in[i].useinode(name, v);
				break;
			}
		}

	}
};
class createdisk {
	vector<vector< char > > disk;
	superblock sp1;
public:
	createdisk()
	{
		cout<<"Disk Created and superblock Initialized !"<<endl;
		for (int i = 0; i < 127; i++) {
			vector<char> v1;
			disk.push_back(v1);
		}

	}
	void createfile( char* name, int size) {
		if (size > 8)
		{
			cout << "Cannot Create File as size exceeds Maximum Limit" << endl;
			return;
		}
		vector<int> v;
		v = sp1.findfreeblocks(size);
		if (v.size() == 0)
		{
			cout << "Insufficient Disk Space !" << endl;
		}
		sp1.set_file(v, name);
		cout<<"File created successfully\n";
	}
	void ls()
	{
		for (int i = 0; i < sp1.in.size(); i++)
		{
			if (sp1.in[i].used == 1)
			{
				cout << "Name : " << sp1.in[i].name << " Size: " << sp1.in[i].size <<  endl;
			}
		}
	}
	void deletefile(char * name)
	{
		bool flagd = false;
		for (int i = 0; i < sp1.in.size(); i++)
		{
			if (sp1.in[i].used)
			{
				bool flag = true;
				for (int j = 0; j < 8; j++)
				{
					if (sp1.in[i].name[j] != name[j])
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					flagd = true;
					sp1.in[i].used = 0;
					memset(sp1.in[i].name, 0, 8);
					sp1.in[i].size = 0;
					for (int j = 0; j < 8; j++)
					{
						if (sp1.in[i].blockpointer[j] != -1)
						{
							int ind = sp1.in[i].blockpointer[j];
							sp1.arr[ind] = false;
						}
					}
				}
			}
		}
		if (!flagd)
		{
			cout << " No such File to Delete " << endl;
		}
		else
		{
			cout<<"File Deleted successfully\n";
		}

	}
	void writefile(char * name, int blocknum, char* buff)
	{
		bool flagd = false;
		for (int i = 0; i < sp1.in.size(); i++)
		{
			if (sp1.in[i].used)
			{
				bool flag = true;
				for (int j = 0; j < 8; j++)
				{
					if (sp1.in[i].name[j] != name[j])
					{
						flag = false;
						break;
					}
				}
				if (flag && blocknum < sp1.in[i].size)
				{
					flagd = true;
					int index = sp1.in[i].blockpointer[blocknum];
					for (int k = 0; k < 1024; k++)
					{
						disk[index].push_back(buff[k]);
					}
				}
			}
		}
		if (!flagd)
		{
			cout << "No such File found ! hence no write Possible" << endl;
		}
		else
		{
			cout<<"Data Written\n";
		}
		return;
	}
	void readfile(char * name, int blocknum, char* buff)
	{
		bool flagd = false;
		for (int i = 0; i < sp1.in.size(); i++)
		{
			if (sp1.in[i].used)
			{
				bool flag = true;
				for (int j = 0; j < 8; j++)
				{
					if (sp1.in[i].name[j] != name[j])
					{
						flag = false;
						break;
					}
				}
				if (flag && blocknum < sp1.in[i].size)
				{
					flagd = true;
					int index = sp1.in[i].blockpointer[blocknum];
					if (disk[index].size() == 0)
					{
						cout << "Block is Empty !" << endl;
						return;
					}
					for (int k = 0; k < disk[index].size(); k++)
					{
						buff[k] = disk[index][k];
					}
				}
			}
		}
		if (!flagd)
		{
			cout << "No such File found or Inappropriate block to write on ! hence no write Possible" << endl;
		}
		return;

	}
};

void header()
{
    cout<<"CS558 : COMPUTER SYSTEM LAB ASSIGNMENT - 05\n";
    cout<<"Instructor : Dr. Manas Khatua and Dr. Moumita Patra\n";
    cout<<"TA's : Alakesh Kalita, Arunav Saikia, Meenu Rani Dey, Priya Undriwade, Vinay Kumar Gupta\n";
    cout<<"Sumbittted By : Himanshu Patel(204101029), Ketan Karnakota(204101030)\n";
}
int main()
{
	header();
	createdisk disk=createdisk();

	while(true)
	{
		cout<<"1. Create file\n2. Delete File\n3. List all files\n4. Read from a file\n5. Write to a File\nEnter -1 to exit\n";
		int choice;
		cout<<"Enter your choice :";
		cin>>choice;
		string file_name;
		char buffer[1024];
		int blocknum;
		int size;
		switch(choice)
		{
			case 1: cout<<"Enter the name of file :";
					cin>>file_name;
					cout<<"Enter the size of file :";
					cin>>size;
					disk.createfile(&*file_name.begin(),size);
					break;
			case 2: cout<<"Enter the name of file to be deleted :";
					cin>>file_name;
					disk.deletefile(&*file_name.begin());
					break;
			case 3: cout<<"------------------------\n";
					disk.ls();
					break;

			case 4: cout<<"Enter the file name from which data is to be read :";
					cin>>file_name;
					cout<<"Enter the block number in the file :";
					cin>>blocknum;
					disk.readfile(&*file_name.begin(),blocknum,buffer);
					cout<<buffer<<endl;
					memset(buffer,'0',1024);
					break;
			case 5: cout<<"Enter the file name where you want to write :";
					cin>>file_name;
					cout<<"Enter the block Number in the file :";
					cin>>blocknum;
					cout<<"Enter the data to be wriiten :\n";
					memset(buffer,'0',1024);
					cin.ignore();
					cin.getline(buffer,1024);
					disk.writefile(&*file_name.begin(),blocknum,buffer);
					break;
			default :cout<<"Thankyou!!"; exit(-1);
		}
		cout<<"----------------------------------------------------------------------\n";
	}

	return 0;
}


