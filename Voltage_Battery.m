clear all;
clc;

VB0=0;
VB1=-10;
CFVBFLT=0.5;

VBFLT=zeros(5,2);
VBFLT(1,1)=nan;
VBFLT(1,2)=VB0;

i=2;
while i<6
    temp=VB0;
    VB0=VB1;
    VB1=temp;
    VBFLT(i,1)=VBFLT(i-1,2);
    VBFLT(i,2)=VB0*CFVBFLT+VBFLT(i,1)*(1-CFVBFLT);
    i=i+1;
end
    