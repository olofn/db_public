#include <allegro.h>///////////////////////////////////////////////Untangle v2.0
#define p(i) x[i],y[i]////////////////////////////////////////////By Per Larsson
x[99],y[99],e[99][99],w=600,l;*c(a,b){return a<b?e[a]+b:e[b]+a;}_(a,b,c){return
b<c?a>=b&&a<=c:a>=c&&a<=b;}q(w,e,r,t,y,u,i,o){int A=t-e,B=w-r,C=A*w+B*e,D=o-u,E=
y-i,F=D*y+E*u,d=A*E-D*B,X=(E*C-B*F),Y=(A*F-D*C);return d?_(X/d,w,r)&&_(Y/d,e,t)
&&_(X/d,y,i)&&_(Y/d,u,o):0;}M(i,j){int I,J,f=0;for(I=0;I<l;I++)for(J=0;J<l;J++)f
+=j!=I&&i!=J&&i!=I&&j!=J&&*c(I,J)&&q(p(i),p(j),p(I),p(J));return f;}main(){int i
,I,j,J,f,F,a,b,s=-1,X,Y,H,h;BITMAP*B;SAMPLE*S;allegro_init();*c(0,1)=*c(0,2)=*c(
0,3)=1;set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,w,0,0);install_sound(DIGI_DIRECTX(
0),MIDI_NONE,0);B=create_bitmap(w,w);install_keyboard();install_mouse();*c(2,3)=
*c(1,2)=*c(1,3)=1;text_mode(-1);S=create_sample(8,0,9999,9999);for(i=0;i<9999;i
++){((unsigned char*)S->data)[i]=(((i+(fixsin(i<<13)>>13))%100+(i)%152)*i)/9000;
}for(l=4;l<99;l++){play_sample(S,255,55,1600,0);play_sample(S,255,200,1604,0);
for(i=0;i<l;i++){x[i]=((fixcos((i<<24)/l)*w/3)>>16)+w/2;y[i]=((fixsin((i<<24)/l)
*w/3)>>16)+w/2;}do{F=0;key[KEY_ESC]?exit(0):0;clear_to_color(B,15);for(i=0;i<l;i
++){for(j=0;j<l;j++){f=0;if(*c(j,i)){f=M(i,j);for(a=-1;a<2;a++)for(b=-1;b<2;b++)
line(B,a+p(i)+b,a+p(j)+b,f?12:10);}F|=f;}}for(i=0;i<l;i++){circlefill(B,p(i),8,0
);circlefill(B,p(i),6,s==i?7:8);s=mouse_b?s:-1;if(mouse_b&&s<0&&_(mouse_x-x[i],-
7,7)&&_(mouse_y-y[i],-7,7))s=i;}if(s>=0){x[s]=mouse_x;y[s]=mouse_y;}textprintf(B
,font,10,10,0,"Level %d",l-3);draw_sprite(B,mouse_sprite,mouse_x,mouse_y);blit(B
,screen,0,0,0,0,w,w);}while(F||mouse_b);H=0;for(j=0;j<2000;j++){h=0;x[l]=rand()%
w*2-w/2;y[l]=rand()%w*2-w/2;for(i=0;i<l;i++){h+=M(i,l)==0;}if(h>H){H=h;X=x[l];Y=
y[l];}}x[l]=X;y[l]=Y;for(i=0;i<l;i++){*c(i,l)=M(i,l)==0;*c(rand()%l,rand()%l)=0;
}}}END_OF_MAIN();///////////////////////////////////////////////////////////////