#include "Filters.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

using std::min;
using std::max;

namespace ImageFilters {
static int clamp(int v) { return max(0, min(255, v)); }

static void grayscale(Image& im) {
    for (int y=0;y<im.height;y++) for(int x=0;x<im.width;x++) {
        int g=(im.getPixel(x,y,0)+im.getPixel(x,y,1)+im.getPixel(x,y,2))/3;
        for(int c=0;c<3;c++) im.setPixel(x,y,c,g);
    }
}
static void blackWhite(Image& im) {
    for(int y=0;y<im.height;y++) for(int x=0;x<im.width;x++) {
        int g=(im.getPixel(x,y,0)+im.getPixel(x,y,1)+im.getPixel(x,y,2))/3; int v=g<128?0:255;
        for(int c=0;c<3;c++) im.setPixel(x,y,c,v);
    }
}
static void invert(Image& im) {
    for(int y=0;y<im.height;y++) for(int x=0;x<im.width;x++) for(int c=0;c<3;c++) im.setPixel(x,y,c,255-im.getPixel(x,y,c));
}
static void frame(Image& im, int style) {
    int border=min(20,min(im.width/2,im.height/2));
    for(int y=0;y<im.height;y++) for(int x=0;x<im.width;x++) {
        bool outer=x<border||x>=im.width-border||y<border||y>=im.height-border;
        bool inner=style==2 && !outer && (x<border+5||x>=im.width-border-5||y<border+5||y>=im.height-border-5);
        if(outer||inner) { int col[3]; if(inner){col[0]=col[1]=col[2]=255;} else {col[0]=30;col[1]=110;col[2]=235;} for(int c=0;c<3;c++) im.setPixel(x,y,c,col[c]); }
    }
}
static void flip(Image& im, int mode) {
    Image out(im.width,im.height);
    for(int y=0;y<im.height;y++) for(int x=0;x<im.width;x++) for(int c=0;c<3;c++) out.setPixel(mode==1?im.width-1-x:x,mode==2?im.height-1-y:y,c,im.getPixel(x,y,c));
    im=out;
}
static void rotate(Image& im, int deg) {
    if(deg==180) { Image out(im.width,im.height); for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++)out.setPixel(im.width-1-x,im.height-1-y,c,im.getPixel(x,y,c)); im=out; return; }
    Image out(im.height,im.width);
    for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++) out.setPixel(deg==90?im.height-1-y:y,deg==90?x:im.width-1-x,c,im.getPixel(x,y,c));
    im=out;
}
static void brightness(Image& im,int pct) {
    double f=pct<0?1.0+pct/100.0:1.0+pct/100.0;
    for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++){int v=im.getPixel(x,y,c); im.setPixel(x,y,c,clamp((int)(pct<0?v*f:v*f)));}
}
static void resizeImage(Image& im,int w,int h) {
    if(w<1||h<1||w>10000||h>10000) throw std::runtime_error("Invalid output dimensions.");
    double sx=(double)im.width/w, sy=(double)im.height/h; Image out(w,h);
    for(int y=0;y<h;y++)for(int x=0;x<w;x++)for(int c=0;c<3;c++)out.setPixel(x,y,c,im.getPixel(min(im.width-1,(int)(x*sx)),min(im.height-1,(int)(y*sy)),c)); im=out;
}
static void merge(Image& im,const std::string& path) {
    Image second(path); int w=min(im.width,second.width),h=min(im.height,second.height);
    for(int y=0;y<h;y++)for(int x=0;x<w;x++)for(int c=0;c<3;c++) im.setPixel(x,y,c,(im.getPixel(x,y,c)+second.getPixel(x,y,c))/2);
}
static void edges(Image& im) {
    Image out(im.width,im.height);
    for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++){
        int g=(im.getPixel(x,y,0)+im.getPixel(x,y,1)+im.getPixel(x,y,2))/3;
        int rg=g,dg=g;
        if(x+1<im.width)rg=(im.getPixel(x+1,y,0)+im.getPixel(x+1,y,1)+im.getPixel(x+1,y,2))/3;
        if(y+1<im.height)dg=(im.getPixel(x,y+1,0)+im.getPixel(x,y+1,1)+im.getPixel(x,y+1,2))/3;
        int v=(abs(g-rg)+abs(g-dg)>35)?0:255; for(int c=0;c<3;c++)out.setPixel(x,y,c,v);
    } im=out;
}
static void crop(Image& im,int x0,int y0,int w,int h) {
    if(x0<0||y0<0||w<1||h<1||x0+w>im.width||y0+h>im.height) throw std::runtime_error("Crop area is outside the image.");
    Image out(w,h); for(int y=0;y<h;y++)for(int x=0;x<w;x++)for(int c=0;c<3;c++)out.setPixel(x,y,c,im.getPixel(x0+x,y0+y,c)); im=out;
}
static void blur(Image& im,int radius) {
    if(radius<1||radius>5)throw std::runtime_error("Blur strength must be from 1 to 5."); Image out(im.width,im.height);
    for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++){int total=0,n=0;for(int dy=-radius;dy<=radius;dy++)for(int dx=-radius;dx<=radius;dx++){int nx=x+dx,ny=y+dy;if(nx>=0&&nx<im.width&&ny>=0&&ny<im.height){total+=im.getPixel(nx,ny,c);n++;}}out.setPixel(x,y,c,total/n);} im=out;
}
static void sunlight(Image& im) {for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++)im.setPixel(x,y,c,clamp(im.getPixel(x,y,c)+45));}
static void oldTV(Image& im) {for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++){int g=(im.getPixel(x,y,0)+im.getPixel(x,y,1)+im.getPixel(x,y,2))/3;if(y%4==0)g=g*3/4;for(int c=0;c<3;c++)im.setPixel(x,y,c,g);}}
static void purple(Image& im) {for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++){int r=im.getPixel(x,y,0),g=im.getPixel(x,y,1),b=im.getPixel(x,y,2);im.setPixel(x,y,0,clamp(r+35));im.setPixel(x,y,1,g*3/4);im.setPixel(x,y,2,clamp(b+55));}}
static void infrared(Image& im) {for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++){int r=im.getPixel(x,y,0),g=im.getPixel(x,y,1),b=im.getPixel(x,y,2);im.setPixel(x,y,0,255-g);im.setPixel(x,y,1,255-b);im.setPixel(x,y,2,255-r);}}
static void skew(Image& im,double angle) {
    if(angle<5||angle>30)throw std::runtime_error("Skew angle must be between 5 and 30 degrees."); double t=tan(angle*3.14159265358979323846/180.0);int extra=max(1,(int)(im.height*t));Image out(im.width+extra,im.height);
    for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++)out.setPixel(x+(int)((im.height-1-y)*t),y,c,im.getPixel(x,y,c)); im=out;
}
static void oil(Image& im) {
    Image out(im.width,im.height);for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++)for(int c=0;c<3;c++){int sum=0,n=0;for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){int nx=x+dx,ny=y+dy;if(nx>=0&&nx<im.width&&ny>=0&&ny<im.height){sum+=im.getPixel(nx,ny,c);n++;}}out.setPixel(x,y,c,(sum/n/32)*32);}im=out;
}
void apply(Image& image,int number,int p1,int p2,int p3,int p4,double d1,const std::string& extraFile) {
    switch(number) {
    case 1: grayscale(image); break; case 2: blackWhite(image); break; case 3: invert(image); break;
    case 4: frame(image,p1); break; case 5: flip(image,p1); break; case 6: rotate(image,p1); break;
    case 7: brightness(image,p1); break; case 8: resizeImage(image,p1,p2); break; case 9: merge(image,extraFile); break;
    case 10: edges(image); break; case 11: crop(image,p1,p2,p3,p4); break;
    case 12: blur(image,p1); break; case 13: sunlight(image); break; case 14: oldTV(image); break;
    case 15: purple(image); break; case 16: infrared(image); break; case 17: skew(image,d1); break; case 18: oil(image); break;
    default: throw std::runtime_error("Choose a number from 1 to 18.");
    }
}
}
