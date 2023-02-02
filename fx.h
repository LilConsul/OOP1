#ifndef LB1_FX_H
#define LB1_FX_H

namespace std {

    class fx {
    private:
        int *x;
        int *n;
        bool isX;
        bool isNum;
        bool isDivX;
        bool isXPow;
        bool isPowX;
        bool isCos;
        bool isSin;

        string fx_str;
        string buffer;

        void check();
        string p_Check(string output);
        string num();
        string divv();
        string xPow();
        string powX();
        string cosX();
        string sinX();
    public:
        fx();
        ~fx();
        void input_fx(void);
        string antiderr(void);
    };

}

#endif //MAIN_CPP_FX_H
