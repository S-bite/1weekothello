int main(){
    char c=0x80;
    cout<<(int)c<<endl;
    c<<=1;
    cout<<(int)c<<endl;
    State s;
    s.m.setStone(Pos(0,0),BLACK);
    s.m.setStone(Pos(3,3),BLACK);
    s.m.setStone(Pos(4,4),BLACK);
    s.m.setStone(Pos(4,3),WHITE);
    s.m.setStone(Pos(3,4),WHITE);
    s.draw();
    s.m.boardBlack=s.m.shiftBoardLeft(s.m.boardBlack);
    s.m.boardWhite=s.m.shiftBoardLeft(s.m.boardWhite);
    s.draw();
return 0;
}