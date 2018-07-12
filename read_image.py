
# coding: utf-8

# In[1]:


from PIL import Image
from glob import glob
from os.path import splitext
import matplotlib.pyplot as plt
import matplotlib.image as img
import numpy as np
import sys

# In[2]:


#sys.argv[1]
picture = img.imread('Images/' + sys.argv[1])
stage_picture = [0,0,0,0,0]
for i in range(5):
    stage_picture[i] = img.imread('Images/stage_'+str(i+1)+'.png')
recover_daimond_picture = []
for i in range(10):
    recover_daimond_picture.append(img.imread('Images/Recover_Diamond'+str(i+1)+'.png'))
cd_picture = []
for i in range(4):
    cd_picture.append(img.imread('Images/CD'+str(i+1)+'.png'))
TransferShield_picture = img.imread('Images/TransferShield.png')
EasyHarm_picture = img.imread('Images/EasyHarm.png')
MinusHarm_picture = img.imread('Images/MinusHarm.png')
Stregthen_picture = img.imread('Images/Stregthen.png')
enemy_num = [3,3,1,1,2]
enemy_picture = [[],[],[],[],[]]
for st in range(5):
    for no in range(enemy_num[st]):
        enemy_picture[st].append(img.imread('Images/Stage_'+str(st+1)+'_no'+str(no+1)+'.png'))


# In[3]:


fp = open("info.txt", "w")

stage_and_enemy_ans = []
daimond_ans = [[],[]]
me_death_and_hp_ans=[0,0,0,0,0,0]
me_streng_and_minus=[0,0,0,0,0,0]
me_relife=[]
enemy_kind_hp_shild=[]
enemy_cd_ans=[]
enemy_status=[]


# In[4]:


#daimond
for r in range(2):
    #print(' ')
    for c in range(7):
        ans=[0,0,0]
        perl = picture[535+r*100:545+r*100,360+c*100:370+c*100,:]
        tmp=np.mean(perl, axis=0)
        tmp=np.mean(tmp, axis=0)
        if(tmp[0]-tmp[2]>0.25 and tmp[1]-tmp[2]>0.25):
            ans[0]=ans[0]+1
        elif(tmp[2]-tmp[0]>0.25 and tmp[2]-tmp[1]>0.25):
            ans[1]=ans[1]+1
        elif(np.mean(tmp)>0.8):
            ans[2]=ans[2]+1
        perl = picture[540+r*100:550+r*100,360+c*100:370+c*100,:]
        tmp=np.mean(perl, axis=0)
        tmp=np.mean(tmp, axis=0)
        if(tmp[0]-tmp[2]>0.25 and tmp[1]-tmp[2]>0.25):
            ans[0]=ans[0]+1
        elif(tmp[2]-tmp[0]>0.25 and tmp[2]-tmp[1]>0.25):
            ans[1]=ans[1]+1
        elif(np.mean(tmp)>0.8):
            ans[2]=ans[2]+1
        perl = picture[535+r*100:545+r*100,365+c*100:375+c*100,:]
        tmp=np.mean(perl, axis=0)
        tmp=np.mean(tmp, axis=0)
        if(tmp[0]-tmp[2]>0.25 and tmp[1]-tmp[2]>0.25):
            ans[0]=ans[0]+1
        elif(tmp[2]-tmp[0]>0.25 and tmp[2]-tmp[1]>0.25):
            ans[1]=ans[1]+1
        elif(np.mean(tmp)>0.8):
            ans[2]=ans[2]+1
        perl = picture[540+r*100:550+r*100,365+c*100:375+c*100,:]
        tmp=np.mean(perl, axis=0)
        tmp=np.mean(tmp, axis=0)
        if(tmp[0]-tmp[2]>0.25 and tmp[1]-tmp[2]>0.25):
            ans[0]=ans[0]+1
        elif(tmp[2]-tmp[0]>0.25 and tmp[2]-tmp[1]>0.25):
            ans[1]=ans[1]+1
        elif(np.mean(tmp)>0.8):
            ans[2]=ans[2]+1
        if(ans[0]>ans[1] and ans[0]>ans[2]):
            daimond_ans[r].append(0)
        elif(ans[1]>ans[0] and ans[1]>ans[2]):
            daimond_ans[r].append(1)
        elif(ans[2]>ans[0] and ans[2]>ans[1]):
            daimond_ans[r].append(2)
        else:
            daimond_ans[r].append(1)


# In[5]:


# player alive or dead

life=[0,0,0]

HP_dica = picture[350:355, 116:196, :]
tmp=np.mean(HP_dica, axis=0)
tmp=np.mean(tmp, axis=0)
if(tmp[0]-tmp[1]>0.18 and tmp[0]-tmp[2]>0.18):
    me_death_and_hp_ans[2]=1
elif(tmp[0]-tmp[1]<0.18 and tmp[0]-tmp[2]<0.18):
    life[0]=1

HP_naya = picture[434:439, 261:341, :]
tmp=np.mean(HP_naya, axis=0)
tmp=np.mean(tmp, axis=0)
if(tmp[0]-tmp[1]>0.18 and tmp[0]-tmp[2]>0.18):
    me_death_and_hp_ans[1]=1
elif(tmp[0]-tmp[1]<0.18 and tmp[0]-tmp[2]<0.18):
    life[1]=1

HP_pon = picture[360:365, 442:522, :]
tmp=np.mean(HP_pon, axis=0)
tmp=np.mean(tmp, axis=0)
if(tmp[0]-tmp[1]>0.18 and tmp[0]-tmp[2]>0.18):
    me_death_and_hp_ans[0]=1
elif(tmp[0]-tmp[1]<0.18 and tmp[0]-tmp[2]<0.18):
    life[2]=1


# In[6]:


# player HP

HP=[]
for i in range(len(life)):
    HP.append(life[i])

# full blood: [0.72, 0.37, 0.20, 1]
HP_dica = picture[360:368, 116:196, :]
two=HP_dica[:, 21:22, :]
three=HP_dica[:, 41:42, :]
four=HP_dica[:, 61:62, :]
tmp=np.mean(np.mean(two, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[0]=1
tmp=np.mean(np.mean(three, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[0]=2
tmp=np.mean(np.mean(four, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[0]=3
me_death_and_hp_ans[5]=HP[0]

HP_naya = picture[444:452, 261:341, :]
two=HP_naya[:, 21:22, :]
three=HP_naya[:, 41:42, :]
four=HP_naya[:, 61:62, :]
tmp=np.mean(np.mean(two, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[1]=1
tmp=np.mean(np.mean(three, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[1]=2
tmp=np.mean(np.mean(four, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[1]=3
me_death_and_hp_ans[4]=HP[1]

HP_pon = picture[370:378, 442:522, :]
two=HP_pon[:, 21:22, :]
three=HP_pon[:, 41:42, :]
four=HP_pon[:, 61:62, :]
tmp=np.mean(np.mean(two, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[2]=1
tmp=np.mean(np.mean(three, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[2]=2
tmp=np.mean(np.mean(four, axis=0), axis=0)
if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
    HP[2]=3
me_death_and_hp_ans[3]=HP[2]


# In[7]:


#player state

feature_dica = picture[335:349, 105:119, :]
Ediff = np.mean(abs(EasyHarm_picture-feature_dica))
Mdiff = np.mean(abs(MinusHarm_picture-feature_dica))
Sdiff = np.mean(abs(Stregthen_picture-feature_dica))
if(Mdiff<0.1):
    me_streng_and_minus[5]=1
elif(Sdiff<0.1):
    me_streng_and_minus[2]=1

feature_naya = picture[419:433, 250:264, :]
Ediff = np.mean(abs(EasyHarm_picture-feature_naya))
Mdiff = np.mean(abs(MinusHarm_picture-feature_naya))
Sdiff = np.mean(abs(Stregthen_picture-feature_naya))
if(Mdiff<0.1):
    me_streng_and_minus[4]=1
elif(Sdiff<0.1):
    me_streng_and_minus[1]=1

feature_pon = picture[345:359, 432:446, :]
Ediff = np.mean(abs(EasyHarm_picture-feature_pon))
Mdiff = np.mean(abs(MinusHarm_picture-feature_pon))
Sdiff = np.mean(abs(Stregthen_picture-feature_pon))
if(Mdiff<0.1):
    me_streng_and_minus[3]=1
elif(Sdiff<0.1):
    me_streng_and_minus[0]=1


# In[8]:


#player need daimond to relife

num_dica = picture[352:377, 77:102, :]
minn=1
ans=0
if(life[0]==0):
    for cd in range(10):
        diff=np.mean(abs(num_dica-recover_daimond_picture[cd]))
        if(diff<minn):
            minn=diff
            ans=cd+1
me_relife.append(ans)

num_naya = picture[436:461, 222:247, :]
minn=1
ans=0
if(life[1]==0):
    for cd in range(10):
        diff=np.mean(abs(num_naya-recover_daimond_picture[cd]))
        if(diff<minn):
            minn=diff
            ans=cd+1
me_relife.append(ans)

num_pon = picture[362:387, 404:429, :]
minn=1
ans=0
if(life[2]==0):
    for cd in range(10):
        diff=np.mean(abs(num_pon-recover_daimond_picture[cd]))
        if(diff<minn):
            minn=diff
            ans=cd+1
me_relife.append(ans)


# In[9]:


stage=picture[33:68, 328:348, :]

s=[0,0,0,0,0]
for i in range(5):
    s[i]=np.mean(abs(stage-stage_picture[i]))

minn=s[0]
stage_index=0
for i in range(5):
    if(s[i]<minn):
        stage_index=i
        minn=s[i]

stage_and_enemy_ans.append(stage_index+1)


# In[10]:


enemy_location = [[[370, 794], [444, 976], [359, 1119]], 
                  [[374, 820], [448, 992], [363, 1118]], 
                  [[375, 961]], 
                  [[370, 977]], #384 994
                  [[372, 891], [446, 1050]]]

enemy_kind = [[0, 0, 0], 
              [1, 1, 2], 
              [3], 
              [4], #384 994
              [5, 2]]


# In[11]:


live=[]

enemy_leftup = [[[100, 745], [180, 920], [90, 1060]],
               [[100, 755], [180, 925], [90, 1085]],
               [[110, 895]],
               [[100, 915]],
               [[100, 850], [150, 1015]]]

enemy = enemy_leftup[stage_index]
enemy_cnt=0
for i in range(len(enemy)):
    monster = picture[enemy[i][0]:enemy[i][0]+250, enemy[i][1]:enemy[i][1]+200, :]
    diff = np.mean(abs(monster-enemy_picture[stage_index][i]))
    blue = np.mean(monster, axis=0)
    blue = np.mean(blue, axis=0)
    dead_point=diff+blue[2]*2-blue[0]-blue[1]
    if(dead_point>0.44):
        live.append(0)
    else:
        live.append(1)
        enemy_cnt=enemy_cnt+1
        enemy_kind_hp_shild.append(enemy_kind[stage_index][i])
stage_and_enemy_ans.append(enemy_cnt)


# In[12]:


HP_offset = [-4, 26]

HP=[]
for i in range(len(live)):
    HP.append(live[i])

enemy = enemy_location[stage_index]

for i in range(len(enemy)):
    if(live[i]==0):
        continue
    hp=picture[enemy[i][0]-4:enemy[i][0]+4, enemy[i][1]+26:enemy[i][1]+106, :]
    two=hp[:, 21:22, :]
    three=hp[:, 41:42, :]
    four=hp[:, 61:62, :]
    tmp=np.mean(np.mean(two, axis=0), axis=0)
    if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
        HP[i]=1
    tmp=np.mean(np.mean(three, axis=0), axis=0)
    if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
        HP[i]=2
    tmp=np.mean(np.mean(four, axis=0), axis=0)
    if(tmp[0]>0.3 or tmp[1]>0.3 or tmp[2]>0.3):
        HP[i]=3
    enemy_kind_hp_shild.append(HP[i])


# In[13]:


shield_offset = [14, 17]
SHIELD=[]
for i in range(len(live)):
    SHIELD.append(0)

enemy = enemy_location[stage_index]

for i in range(len(enemy)):
    if(live[i]==0):
        continue
    shield=picture[enemy[i][0]+14:enemy[i][0]+17, enemy[i][1]+17:enemy[i][1]+97, :]
    two=shield[:, 21:22, :]
    three=shield[:, 41:42, :]
    four=shield[:, 61:62, :]
    tmp=np.mean(np.mean(two, axis=0), axis=0)
    if(tmp[0]>0.6 or tmp[1]>0.6 or tmp[2]>0.6):
        SHIELD[i]=1
    tmp=np.mean(np.mean(three, axis=0), axis=0)
    if(tmp[0]>0.6 or tmp[1]>0.6 or tmp[2]>0.6):
        SHIELD[i]=2
    tmp=np.mean(np.mean(four, axis=0), axis=0)
    if(tmp[0]>0.6 or tmp[1]>0.6 or tmp[2]>0.6):
        SHIELD[i]=3
    enemy_kind_hp_shild.append(SHIELD[i])


# In[14]:


enemy_cd = [[[360,785], [434, 967], [349, 1110]],
            [[363,813], [437, 984], [353, 1112]],
            [[364,954]],
            [[360,970]],
            [[361,884], [435, 1043]]]

CD =[]
for i in range(len(live)):
    CD.append(live[i])

cd_loc = enemy_cd[stage_index]
for i in range(len(cd_loc)):
    if(live[i]==0):
        continue
    cd_num = picture[cd_loc[i][0]:cd_loc[i][0]+23, cd_loc[i][1]:cd_loc[i][1]+20, :]
    minn=1
    ans=0
    if(live[i]==1):
        for cd in range(4):
            diff=np.mean(abs(cd_num-cd_picture[cd]))
            if(diff<minn):
                minn=diff
                ans=cd+1
        CD[i]=ans
    enemy_cd_ans.append(CD[i])


# In[15]:


for i in range(len(cd_loc)):
    if(live[i]==0):
        continue
    status = picture[cd_loc[i][0]-18:cd_loc[i][0]-4, cd_loc[i][1]+25:cd_loc[i][1]+39, :]
    Ediff = np.mean(abs(EasyHarm_picture-status ))
    if(Ediff<0.1):
        enemy_status.append(1)
    else:
        enemy_status.append(0)
        
for i in range(len(cd_loc)):
    if(live[i]==0):
        continue
    status = picture[cd_loc[i][0]-18:cd_loc[i][0]-4, cd_loc[i][1]+25:cd_loc[i][1]+39, :]
    Tdiff = np.mean(abs(TransferShield_picture-status ))
    if(Tdiff<0.1):
        enemy_status.append(1)
    else:
        enemy_status.append(0)


# In[16]:


text=''
for i in range(len(stage_and_enemy_ans)):
    if(i!=0):
        text+=' '
    text+=str(stage_and_enemy_ans[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(daimond_ans[0])):
    if(i!=0):
        text+=' '
    text+=str(daimond_ans[0][i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(daimond_ans[1])):
    if(i!=0):
        text+=' '
    text+=str(daimond_ans[1][i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(me_death_and_hp_ans)):
    if(i!=0):
        text+=' '
    text+=str(me_death_and_hp_ans[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(me_streng_and_minus)):
    if(i!=0):
        text+=' '
    text+=str(me_streng_and_minus[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(me_relife)):
    if(i!=0):
        text+=' '
    text+=str(me_relife[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(enemy_kind_hp_shild)):
    if(i!=0):
        text+=' '
    text+=str(enemy_kind_hp_shild[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(enemy_cd_ans)):
    if(i!=0):
        text+=' '
    text+=str(enemy_cd_ans[i])
text+='\n'
print(text)
fp.write(text)

text=''
for i in range(len(enemy_status)):
    if(i!=0):
        text+=' '
    text+=str(enemy_status[i])
text+='\n'
print(text)
fp.write(text)


# In[17]:


fp.close()

