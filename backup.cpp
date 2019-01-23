#include<bits/stdc++.h>
using namespace std;
int DownLoad(const string &url,const string &addr)
{
	string cmd="powershell $client = new-object System.Net.WebClient ; $client.DownloadFile('"+url+"','"+addr+"')";
	return system(cmd.c_str());
}
void load(string &filename,char *s,int maxlen,int &len)
{
	FILE *fin=fopen(filename.c_str(),"rb");
	memset(s,0,maxlen);
	len=fread(s,1,maxlen,fin);
	fclose(fin);
}
inline string i_s(int i)
{
	stringstream ss;
	ss<<i;
	string res;
	ss>>res;
	return res;
}
inline string lna(string &s)
{
	for(int i=s.size()-1;i>=0;i--) if(s[i]=='.') return s.substr(i,s.size());
}
const int maxlen=10000005;
char s[maxlen]; int len;
set<string> urls;
regex have_pic("(http|https).+(.png|.jpg|.jpeg|.gif|.svg).+");
regex is_pic("(http|https).+(.png|.jpg|.jpeg|.gif|.svg)");
int main(int argc,char** argv)
{
	assert(argc>=2);
	string filename=argv[1];
	load(filename,s,maxlen,len);
	for(int i=0;i<len;i++) if(!isprint(s[i])) s[i]=' ';
	string txt=s;
	for(int i=0;i<len;i++)
	{
		if(txt[i]!='h'||txt[i+1]!='t'||txt[i+2]!='t'||txt[i+3]!='p') continue;
		int res=len-i,L=0,R=len-i;
		string str=txt.substr(i,R);
		if(!regex_match(str,have_pic)) continue;
		while(L<=R)
		{
			int mid=(L+R)/2;
			str=txt.substr(i,mid);
			if(regex_match(str,have_pic)||regex_match(str,is_pic)) res=mid,R=mid-1;
			else L=mid+1;
		}
		str=txt.substr(i,res);
		if(!regex_match(str,is_pic)) continue;
		int lasti=i,lastlen=res;
		i++; res--;
		while(res>0)
		{
			str=txt.substr(i,res);
			if(regex_match(str,is_pic)) lasti=i,lastlen=res;
			i++; res--;
		}
		str=txt.substr(lasti,lastlen);
		if(str.size()>100) continue;
		urls.insert(str);
		i--;
		cout<<str<<endl;
	}
	int cnt=0;
	ofstream fout("hst.txt");
	for(auto it=urls.begin();it!=urls.end();it++)
	{
		cnt++;
		string url=*it,addr="files/"+i_s(cnt)+lna(url);
		cout<<"url="<<url<<" addr="<<addr<<endl;
		int flag=DownLoad(url,addr);
		fout<<cnt<<" "<<flag<<" "<<url<<" "<<addr<<endl;
	}
	fout.close();
	system("pause");
	return 0;
}
