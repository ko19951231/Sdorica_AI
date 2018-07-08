# Sdorica AI

## 編譯
 Training `make -f Makefile_train`
 Demo 'make -f Makefile_demo'
 
 Training 會產出執行檔:ai
 Demo 會產出執行檔: demo

## 玩法

- 你會先看到一個初始遊戲盤面
- 請選擇一串你要消掉的珠子
- 依照滑動的珠子位置輸入
- 例如盤面為
- YPYYYWW
- PYWPYYP
- 其中Y為黃色珠子
- P為紫色珠子
- W為白色珠子
- 假如你想消掉的是第二行的兩個黃色珠子
- 請先輸入珠子數量 2
- 再輸入那兩顆珠子的座標 2 5 2 6
- 即會印出你攻擊完後的遊戲畫面
- 並且印出對方攻擊完後的遊戲畫面
- 再次輪到你滑動珠子
