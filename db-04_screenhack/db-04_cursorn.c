#include <allegro.h>/////////////////Cursor*n v1.3 By Olof Naessén and Ted Steen
#define F(i,j)for(i=0;i<j;i++)//////////////////////////////////////////////////
int*B,A[99][99999][5],C[99],D[99][10][10][3],E[99][10][10],g=1,o,d,a,r,k,b,i,t,s
=400,l=3,w,q=3000,*u,*e,*z,h=1,f=40,p=10,j=99,X=0,Y=0;*Q(z,x,y,t,s){u=D[z][x][y]
;if(*u!=0){*u=t;u[1]=s;u[2]=0;}}int L(int v){return rand()%v;}*R(x,y,v){rectfill
(B,x*f+X,y*f+Y,x*f+f+Y,y*f+f+Y,v);}*P(x,y,v){textprintf(B,font,x+X,y+Y,0,z,v);}*
v(int c){F(i,j){o=1;F(k,p){F(r,p){u=D[i][r][k];if(*u==0){a=r;b=k;if(i==c)if(u[1]
==0)R(r,k,4);else R(r,k,p);}if(*u==1)if(u[1]!=0){o=0;if(i==c){if(u[2]>0){X=-u[2]
+L(u[2]*2);Y=-u[2]+L(u[2]*2);u[2]--;}R(r,k,3);z="%d";P(r*f+18,k*f+18,u[1]);X=Y=0
;}}if(*u==4){if(u[1]==0){o=0;w=4;}else w=p;if(i==c)circlefill(B,r*f+20,k*f+20,20
,w);}if(*u==3&c==i)R(r,k,0);if(i==c&&E[i][r][k]==1)R(r,k,14);}}D[i][a][b][1]=o;}
}*S(){srand(3);F(i,j)F(k,p)F(r,p)*D[i][r][k]=-1;F(i,j){C[i]=1;r=L(p);k=L(9)+1;Q(
i,r,k,0,0);*D[i+1][r][k]=3;F(a,L(i+1)+i/2)Q(i,L(p),L(9)+1,1,L((i/2)+2)+1);F(a,L(
2))if(i>5)Q(i,L(p),L(9)+1,4,0);}}*main(){allegro_init();S();F(i,j)E[i][L(p)][L(9
)+1]=1;text_mode(-1);install_mouse();install_keyboard();set_gfx_mode(2,s,s,0,0);
B=create_bitmap(s,s);A[g-1][d][3]=0;while(!key[59]){if(d>q){l--;g++;d=0;S();if(l
==0){z="Game Over";P(155,200,0);z="Highest level reached %d";P(100,209,h);}else 
rest(q);}if(l!=0){clear_to_color(B,15);z="Time %d";P(150,9,q-d);z="Score %d";P(9
,19,t);z="Lives %d";P(9,29,l);e=A[g-1][d];v(C[g-1]);*e=mouse_x;e[1]=mouse_y;e[4]
=0;if(mouse_b)e[3]=1;if(!mouse_b&&A[g-1][d-1][3]){e[3]=0;e[4]=1;}F(i,j)F(r,p)F(k
,p){u=D[i][r][k];if(*u==4)u[1]=0;}F(i,g){u=A[i][d];r=*u/f;k=u[1]/f;o=C[i];if(C[i
]==C[g-1])draw_sprite(B,mouse_sprite,*u,u[1]);if(i==g-1)circlefill(B,*u,u[1],4,4
);e=D[o][r][k];if(*e==4&&u[3])e[1]=1;if(u[4]){if(*e==0&&e[1]==1){C[i]++;h=MAX(h,
C[i]);}if(*e==1&&e[1]!=0){e[1]--;e[2]+=4;t++;}u=&E[o][r][k];if(*u==1){*u=0;l++;}
}}d++;}blit(B,screen,0,0,0,0,s,s);rest(9);}}END_OF_MAIN()/////tinyurl.com/6l3ay7