#include <stdio.h>
#include <stdlib.h>
void dfs(int x,int parent);
int table[50][50]={0},c[50]={0},p[50],q[51]={0},N;
long long dp1[50][51]={0},dp2[50][51]={0},temp[51],ans; // 1 without 2 with [node][K]
int main(){
  int K,x,y,i,j,k;
  scanf("%d%d",&N,&K);
  for(i=0;i<N-1;i++){
    scanf("%d%d",&x,&y);
    table[x-1][y-1]=-1;
    table[y-1][x-1]=-1;
  }
  dfs(0,0);
  for(i=0;i<N;i++)
    if(!c[i])
      q[++q[0]]=i;
  while(q[0]){
    x=q[q[0]--];
    dp1[x][0]=dp2[x][0]=1;
    for(i=0;i<N;i++)
      if(table[x][i]==1){
        for(j=1;j<=K;j++)
          temp[j]=0;
        for(j=1;j<=K;j++){
          dp1[x][j]+=dp1[i][j]+dp2[i][j-1];
          for(k=0;k<=j;k++)
            if(k==1)
              temp[j]+=(dp2[i][k]+1)*dp2[x][j-k];
            else
              temp[j]+=dp2[i][k]*dp2[x][j-k];
        }
        for(j=1;j<=K;j++)
          dp2[x][j]=temp[j];
      }
    if(x){
      c[p[x]]--;
      if(!c[p[x]])
        q[++q[0]]=p[x];
    }
  }
  for(i=0,ans=0;i<=K;i++)
    ans+=dp1[0][i]+dp2[0][i];
  printf("%lld",ans);
  return 0;
}
void dfs(int x,int parent){
  int i;
  p[x]=parent;
  for(i=0;i<N;i++)
    if(table[x][i] && i!=parent){
      table[x][i]+=2;
      c[x]++;
      dfs(i,x);
    }
  return;
}
