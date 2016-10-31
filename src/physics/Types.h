//---------------------------------------------------------------------------

#ifndef TypesH
#define TypesH

#include <IniFiles.hpp>
#include <SysUtils.hpp>

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <cstdlib>

#ifndef RSLINAC
#include <system.hpp>
#include <conio.h>
#include <dir.h>
#include <Vcl.Dialogs.hpp>
#else
#include <AnsiString.hpp>
#define __fastcall 
#endif

#include "ConstUnit.h"

#include "Math.hpp"

//#include "Matrix.h"

namespace HellwegTypes {

enum TError {ERR_NO,ERR_NOFILE,ERR_OPENFILE,ERR_COUPLER,ERR_SOLENOID,ERR_BEAM,
				ERR_CURRENT,ERR_DRIFT,ERR_CELL,ERR_CELLS,ERR_OPTIONS,ERR_DUMP,ERR_FORMAT,ERR_SPCHARGE,ERR_NUMBPARTICLE};

enum TBeamParameter {X_PAR,TH_PAR,BX_PAR,BTH_PAR,BETTA_PAR,PHI_PAR} ;
enum TStructureParameter {KSI_PAR,Z_PAR,A_PAR,RP_PAR,B_PAR,ALPHA_PAR,BETTA_F_PAR,RA_PAR,B_EXT_PAR,NUM_PAR} ;
enum TSplineType {ZSPLINE,LSPLINE,CSPLINE,SSPLINE};
enum TChartType {CH_EMITTANCE,CH_SECTION,CH_PORTRAIT,CH_PHASE,CH_ENERGY,CH_BETTA,CH_A,CH_B,CH_ELP,CH_ATT,CH_APP,CH_BEXT,CH_CLEAR};

enum TInputParameter {POWER,SOLENOID,BEAM,CURRENT,DRIFT,CELL,CELLS,OPTIONS,DUMP,COMMENT,UNDEFINED,SPCHARGE};
enum TTrig {SIN,COS,TG,CTG,SEC,CSC};
enum TLoss {LIVE,RADIUS_LOST,PHASE_LOST,BZ_LOST,BX_LOST,B_LOST,STEP_LOST};
enum TGraphType {TRANS_SEC,LONGT_SEC,TRANS_SPACE,LONGT_SPACE,LONGT_MOTION,PHASE_SLID,W_SPEC,F_SPEC,F_NONE};
enum TOptType {BUNCHER,ACCELERATOR};
enum TBeamType {RANDOM,CST_X,CST_Y,CST_R};

const int MaxParameters=9;  //Maximum number of parameters after a keyword. Currently: SAVE
const int NumBessel=6;
int Nslices=1;

struct TInputLine{
    TInputParameter P;
    int N;
    AnsiString S[MaxParameters];
};

struct TParticle
{
    double x;  //x/lmb (-Rb<x<Rb)
    double x0;
    double Th;
    double Bx;
    double Bth;
    double phi;
    double betta;
    double z;
    TLoss lost;
};
struct TDump
{
   std::string File;//char *File;
   int N1;
   int N2;
   bool LiveOnly;
   bool Phase;
   bool Energy;
   bool Radius;
   bool Azimuth;
   bool Vx;
};
struct TCell
{
    double betta;
    double ELP;
    double AL32;
    double AkL;
    double Mode;
    double F0;
    double P0;
	double dF;
	int Mesh;
    bool Drift;
	bool First;
	bool Dump;
	TDump DumpParameters;
};
struct TStructure
{
    double ksi;
    double lmb;
    double P;
    double dF;
    double E;
    double A;
    double Rp;
    double B;
    double alpha;
    double betta;
    double Ra;
    double B_ext;
    bool jump;
    bool drift;
	int CellNumber;
	bool Dump;
	TDump DumpParameters;
};
struct TResult
{
    double Length;
    double AverageEnergy;
    double MaximumEnergy;
    double EnergySpectrum;
    double InputCurrent;
    double BeamCurrent;
    double Captured;
    double BeamRadius;
    double AveragePhase;
    double PhaseLength;
    double BeamPower;
    double LoadPower;
    double Alpha;
    double Betta;
    double Emittance;
    double A;
};
struct TOptResult
{
    double x;
    TResult Result;
};
struct TSplineCoef
{
    double X;
    double Y;
    double A;
    double B;
    double C;
    double D;
    double W;
    double F;
};
struct TSpectrumBar
{
    double x;
    double phase;
    int N;
    double y;  //envelope
    double P;
	double xAv;
	double xRMS;
	double yAv;
	double yRMS;
};
struct TIntegration
{
    double phi;
    double Az;
    double Ar;
    double Hth;
    double betta;
    double bx;
    double bth;
    double r;
    double th;
    double A;
};
struct TIntParameters
{
    double h;
    double bw;
    double w;
    double dL;
    double A;
    double dA;
    double B;
    double E;
    double Bz_ext;
    double Br_ext;
    double Cmag;
    double SumSin;
    double SumCos;
    double *Aqz;
    double *Aqr;
    double gamma;
    bool drift;
};

//---------------------------------------------------------------------------
#ifndef RSLINAC
inline int round(double x){
	return (x-floor(x))>(ceil(x)-x)?ceil(x):floor(x);
}
#endif
//---------------------------------------------------------------------------
inline double sqr(double x){
    return x*x;
}
//---------------------------------------------------------------------------
inline double cub(double x){
    return x*x*x;
}
//---------------------------------------------------------------------------
inline double arctg(double x){
    return atan(x);
}
//---------------------------------------------------------------------------
inline double tg(double x){
    return tan(x);
}
//---------------------------------------------------------------------------
inline double arc(double x){
    return x*pi/180;
}
//---------------------------------------------------------------------------
inline double ln(double x){
    return log(x);
}
//---------------------------------------------------------------------------
inline double log2(double x){
    return log(x)/log(2.);
}
//---------------------------------------------------------------------------
inline double GammaToMeV(double g){
    return We0*(g-1)*1e-6;;
}
//---------------------------------------------------------------------------
inline double MeVToGamma(double W){
    return 1+W*1e6/We0;
}
//---------------------------------------------------------------------------
inline double EnergyToVelocity(double g){
    return sqrt(1-1/sqr(g));
}
//---------------------------------------------------------------------------
inline double VelocityToEnergy(double b){
    return 1/sqrt(1-sqr(b));
}
//---------------------------------------------------------------------------
inline double VelocityToMeV(double b){
    return GammaToMeV(VelocityToEnergy(b));
}
//---------------------------------------------------------------------------
inline double MeVToVelocity(double W){
    return EnergyToVelocity(MeVToGamma(W));
}
//---------------------------------------------------------------------------
inline double RadToDeg(double a){
    return a*180/pi;
}
//---------------------------------------------------------------------------
inline double DegToRad(double phi){
    return phi*pi/180;
}
//---------------------------------------------------------------------------
inline double mod(double x){
    return x>=0?x:-x;
}
//---------------------------------------------------------------------------
inline double sign(double x){
    if (x==0)
        return 0;
    else
        return x>0?1:-1;
}
//---------------------------------------------------------------------------
inline double PulseToAngle(double bx,double bz){
    if (mod(bz)>1e-5)
        return arctg(bx/bz);
    else
        return sign(bx)*pi/2;
}
//---------------------------------------------------------------------------
inline int Fact(int n){
    int F=1;
    for (int i=1;i<=n;i++)
        F*=i;

    return F;
}
//---------------------------------------------------------------------------
inline double Pow(double x,int n){
    double F=1;

    for (int i=1;i<=n;i++)
        F*=x;

    return F;
}
//---------------------------------------------------------------------------
inline int CountSteps(double delta,double epsilon){
    return ceil(log2(delta/epsilon));
}
//---------------------------------------------------------------------------
inline double Ib0(double x){
    double f=0;

    for (int k=0;k<=NumBessel;k++)
        f+=Pow(x/2,2*k)/sqr(Fact(k));

    return f;
}
//---------------------------------------------------------------------------
inline double Ib1(double x){
    double f=0;

    for (int k=0;k<=NumBessel;k++)
        f+=Pow(x/2,2*k+1)/(Fact(k)*Fact(k+1));

    return f;
}
//---------------------------------------------------------------------------
inline double FormFactor(double p){
    double F1[21]={1.000,0.926,0.861,0.803,0.750,0.704,0.661,0.623,0.588,0.556,
                    0.527,0.500,0.476,0.453,0.432,0.413,0.394,0.378,0.362,0.347,0.333};
    double F2[21]={0.000,0.007,0.020,0.037,0.056,0.075,0.095,0.115,0.135,0.155,
                    0.174,0.192,0.210,0.227,0.244,0.260,0.276,0.291,0.306,0.320,0.333};
    double M=0;
    int i=0;

    if (p<1){
        i=floor(20*p);
        M=F1[i]-(F1[i]-F1[i+1])*(20*p-i);
    }
    else if (p==1)
        M=0.333;
    else if (p>1){
        p=1/p;
        i=floor(20*p);
        M=F2[i]+(F2[i+1]-F2[i])*(20*p-i);
    }

    return M;
}
//---------------------------------------------------------------------------
inline double GetH(double gamma,double phi,double bw,double A)
{
    double H=0;
    H=gamma/bw-sqrt(sqr(gamma)-1)-A*sin(DegToRad(phi))/(2*pi);
    return H;
}
//---------------------------------------------------------------------------
inline int GetSeparatrix(double &gamma,double phi,double bw,double A, double H,bool Neg=false)
{
    double Ah=0, b=0, c=0, D=0;
    int Nroots=0;

    Ah=A*sin(DegToRad(phi))/(2*pi)+H;
    b=Ah/(bw-1/bw);
    c=-(sqr(Ah)+1)/(1-sqr(1/bw));

    D=sqr(b)-c;

    if (D<0)
        Nroots=0;
    else if (D==0) {
        gamma=-b;
        Nroots=1;
    }else {
        if (Neg)
            gamma=-b-sqrt(D);
        else
            gamma=-b+sqrt(D);
        Nroots=2;
    }

    return Nroots;
}
//---------------------------------------------------------------------------
inline int GetPositiveSeparatrix(double &gamma,double phi,double bw,double A, double H)
{
    return GetSeparatrix(gamma,phi,bw,A,H);
}
//---------------------------------------------------------------------------
inline int GetNegativeSeparatrix(double &gamma,double phi,double bw,double A, double H)
{
    return GetSeparatrix(gamma,phi,bw,A,H,1);
}
//---------------------------------------------------------------------------
//--------------------TEXT FILES---------------------------------------------
//---------------------------------------------------------------------------
bool IsNumber(AnsiString &S)   //Checks if the string is a number
{
	double x=0;
	bool Success=false;

	try {                  //Check if the data is really a number
		x=S.ToDouble();
		Success=true;
	}
	catch (...){
		Success=false;
	}
	return Success;
}
//---------------------------------------------------------------------------
bool CheckFile(AnsiString &F)   //Checks if the file exists
{
	bool Exists=false;
	std::ifstream f(F.c_str());

	Exists=f.good();

	f.close();

	return Exists;
}
//---------------------------------------------------------------------------
AnsiString GetWord(ifstream &f)   //Reads the next word from fstream
{
   AnsiString S;
   char s[MAX_CHAR];

   f>>s;
   S=AnsiString(s);

   return S;
}
//---------------------------------------------------------------------------
AnsiString GetLine(ifstream &f)   //Reads the next line from fstream
{
   AnsiString S;
   char s[MAX_CHAR];

   f.getline(s, sizeof(s)) ;
   S=AnsiString(s);

   return S;
}
//---------------------------------------------------------------------------
int NumWords(AnsiString &L)  //Counts number of words in the line
{
	int i=0,Nmax=0,N=0;
	bool Space=true; //Several successive spaces

	Nmax=L.Length();

	while (i<Nmax){
		i++;
		if (L[i]==' ' || L[i]=='\t'){
			if (!Space) //Treat successive spaces as a single
				N++;
			Space=true;
		} else
			Space=false;
	}

	if (!Space)
		N++;

	return N;
}
//---------------------------------------------------------------------------
AnsiString ReadWord(AnsiString &L,int N)   //Parses the Nth word from the string
{
	AnsiString S="";
	int i=1,Nmax=0,W=0;

	Nmax=L.Length();

	while (i<Nmax+1){
		if (L[i]==' ' || L[i]=='\t'){
			if (S==""){  //Treat successive spaces as a single
				i++;
				continue;
			} else{
				W++;
				if (W!=N){  //Not the word we searched
					S="";
					i++;
					continue;
				} else
					break;
			}
		}  else {
			S+=L[i];
			i++;
        }
	}

	return S;
}
//---------------------------------------------------------------------------
int NumPointsInFile(AnsiString &F,int NumRow)
{
	//Check number of valid lines in text file F.
	//Line is valid if number of elements in a row == NumRow and they are numbers
	int N=0;
	AnsiString L,S;
	double x;
	bool Num=false;
	std::ifstream fs(F.c_str());

	while (!fs.eof()){
		L=GetLine(fs);
		if (NumWords(L)==NumRow){       //Check if only two numbers in the line
			for (int i = 0; i < NumRow; i++) {
				S=ReadWord(L,i+1);
				Num=IsNumber(S);
				if (!Num)
					break;
			}
			if (Num)
				N++;
		}
	}
    fs.close();

	return N;
}

};

//---------------------------------------------------------------------------
#endif      // TypesH
