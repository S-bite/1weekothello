class State{
    public:
    bitBoard m;
    void draw(void){
        cout<<"+--------+"<<endl;
        for (int i=63;i>=0;i--){
            if (i%8==7) cout<<"|";
            char c=' ';
            if ((m.boardBlack>>i)&1ll==1) c='x';
            if ((m.boardWhite>>i)&1ll==1) c='o';
            cout<<c;
            if (i%8==0)cout<<"|"<<endl;
        }

        cout<<"+--------+"<<endl;
        return;
    }

};
