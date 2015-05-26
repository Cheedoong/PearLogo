#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;
string s, s_pre, s_suf;

void read_file(const char *filename)
{
    ifstream inf;
    inf.open(filename);
    string sline;
    int stat = 0;
    s = s_pre = s_suf = "";
    while (getline(inf, sline))
    {
        //cout << sline << " " << stat << endl;
        switch (stat)
        {
        case 0:
        {
            if (sline.find("[Begin] These are configurable") != string::npos)
            {
                stat = 1;
            }
            else
            {
                s_pre += sline;
                s_pre += "\n";
            }
            break;
        }
        case 1:
        {
            if (sline.find("[End] These are configurable") != string::npos)
            {
                stat = 2;
            }
            break;
        }
        case 2:
        {
            s_suf += sline;
            s_suf += "\n";
            break;
        }
        }
    }
    inf.close();
}

void process(double r1, double r2, double r3, double a, double b, double c)
{
    s += s_pre;
    ostringstream oss;
    oss <<  "% % % % % % % % [Begin] These are configurable % % % % % % %\n";
    oss <<  "\\FPeval{\\lw}{20}        % linewidth\n";
    oss <<  "\\FPeval{\\rone}{" << r1 << "}    % r1: radius of circle c1\n";
    oss <<  "\\FPeval{\\rtwo}{" << r2 << "}    % r2: 3.14 pi\n";
    oss <<  "\\FPeval{\\rthree}{" << r3 << "} % r3. 18.47 = 32 * Euler's Constant\n";
    oss <<  "\\FPeval{\\rfour}{2.349461690234380417} % to be fixed for higher precision\n";
    oss <<  "\\FPeval{\\a}{" << a << "}         % alpha\n";
    oss <<  "\\FPeval{\\b}{" << b << "}         % beta\n";
    oss <<  "\\FPeval{\\c}{" << c << "}         % gamma\n";
    oss <<  "\\FPeval{\\ydelta}{1.2}   % distance from the top of the pear body to the bottom of the bar\n";
    oss <<  "\\FPeval{\\ll}{1.602}     % lengh of the x-leg of the bar\n";
    oss <<  "% % % % % % % % [End] These are configurable % % % % % % %\n";
    s += oss.str();
    s += s_suf;
}

void write_file(const char *filename)
{
    ofstream outf;
    outf.open(filename);
    outf << s << endl;
    outf.close();
}

void execute(const char *infile, const char *outfile)
{
    read_file(infile);
    int i = 0;
    double r1, r2, r3, a, b, c;
    for (r1 = 3.2; r1 <= 5.4; r1 += 0.4) // 4.36
        for (r2 = 2.4; r2 <= 3.6; r2 += 0.2) // 3.14
            for (r3 = 15; r3 <= 21; r3 += 1) // 18.47
                for (a = 13; a <= 23; a += 2) // 18
                    for (b = 18; b <= 40; b += 2) // 36
                        for (c = 9; b <= 27; c += 3) // 18
                        {
                            i++;
                            process(r1, r2, r3, a, b, c);
                            ostringstream oss;
                            oss << outfile << i << ".tex";
                            string si = oss.str();
                            write_file(si.c_str());
                            char cmd[1024];
                            char jpg_file[256];
                            sprintf(jpg_file, "%s.jpg", si.c_str());
                            sprintf(cmd, "pdflatex %s", si.c_str());
                            system(cmd);
                            sprintf(cmd, "convert %s %s\n", si.c_str(), jpg_file);
                            system(cmd);
                        }
}

int main()
{
    //read_file("PearLogo.tex");
    //cout << s_pre << endl;
    execute("PearLogo.tex", "PearLogo1.tex");
    cout << "Hello world!" << endl;
    return 0;
}
