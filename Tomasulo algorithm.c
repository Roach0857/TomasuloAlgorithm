#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define TEST "test3.txt"
struct Data
{
    char *Dop;
    char *Di;
    char *Dj;
    char *Dk;
    char *Dtag;
    bool *Dflag;
};
struct Buffer
{
    bool *BFbusy;
    char *BFaddress;
    char *BFname;
    int *BFvalue;
};
struct Add
{
    bool *ADbusy;
    char *ADname;
    char *ADop;
    char *ADvj;
    char *ADvk;
    char *ADqj;
    char *ADqk;
    int *ADtime;
};
struct Mult
{
    bool *MUbusy;
    char *MUname;
    char *MUop;
    char *MUvj;
    char *MUvk;
    char *MUqj;
    char *MUqk;
    int *MUtime;
};
struct Register
{
    int *REfloat;
    char *REfloataddress;
    int *REinteger;
    char *REintaddress;
};
struct InstructionStatus
{
    int *ISissue;
    int *IScomp;
    int *ISresult;
};
struct RecordTime
{
    int *CompTime;
    int *ResultTime;
};
int clock = 0;
void CalculationLine(int *);
void LoadData(int *, struct Data *);
void MakeChart(int *, struct Data *, struct Buffer *, struct Buffer *, struct Add *, struct Mult *, struct Register *, struct InstructionStatus *);
void JudgmentAndOperation(int *, int *, struct Data *, struct Buffer *, struct Buffer *, struct Add *, struct Mult *, struct Register *, struct InstructionStatus *, struct RecordTime *);
int main(void)
{
    char str[1] = {0};
    int flag = 1;
    int AmountOfLine = 1;
    CalculationLine(&AmountOfLine);
    //�p����

    struct RecordTime *RT = (struct RecordTime *)malloc(AmountOfLine * sizeof(struct RecordTime));
    RT->CompTime = (int *)calloc(AmountOfLine, sizeof(int));
    RT->ResultTime = (int *)calloc(AmountOfLine, sizeof(int));
    //�ŧi�����ɶ�

    struct Data *DA = (struct Data *)malloc(AmountOfLine * sizeof(struct Data));
    for (int i = 0; i < AmountOfLine; i++)
    {
        DA[i].Dop = (char *)calloc(6, sizeof(char));
        DA[i].Di = (char *)calloc(6, sizeof(char));
        DA[i].Dj = (char *)calloc(6, sizeof(char));
        DA[i].Dk = (char *)calloc(6, sizeof(char));
        DA[i].Dtag = (char *)calloc(6, sizeof(char));
    }
    DA->Dflag = (bool *)calloc(AmountOfLine, sizeof(bool));
    //�ŧi���ɤ��e
    LoadData(&AmountOfLine, DA);
    //Ū�����ɸ��

    struct Buffer *LBF = (struct Buffer *)calloc(2, sizeof(struct Buffer));
    LBF->BFbusy = (bool *)calloc(2, sizeof(bool));
    LBF->BFvalue = (int *)calloc(2, sizeof(int));
    // char *str = (char *)malloc(1 * sizeof(char));

    for (int i = 0; i < 3; i++)
    {
        LBF[i].BFaddress = (char *)calloc(6, sizeof(char));
        LBF[i].BFname = (char *)calloc(6, sizeof(char));
        //itoa(i + 1, str, 10);
        sprintf(str, "%d", (i + 1));
        strcpy(LBF[i].BFname, "load");
        strcat(LBF[i].BFname, str);
    }
    //�ŧibuffer��2��load

    struct Buffer *SBF = (struct Buffer *)calloc(2, sizeof(struct Buffer));
    SBF->BFbusy = (bool *)calloc(2, sizeof(bool));
    SBF->BFvalue = (int *)calloc(2, sizeof(int));

    for (int i = 0; i < 3; i++)
    {
        SBF[i].BFaddress = (char *)calloc(6, sizeof(char));
        SBF[i].BFname = (char *)calloc(6, sizeof(char));
        //itoa(i + 1, str, 10);
        sprintf(str, "%d", (i + 1));
        strcpy(SBF[i].BFname, "store");
        strcat(SBF[i].BFname, str);
    }
    //�ŧibuffer��2��store

    int *Memory = (int *)malloc(64 * sizeof(int));
    //�ŧi�O����j�p
    for (int i = 0; i < 64; i++)
    {
        Memory[i] = 1;
    }
    //��l�ưO���� �w�]��1

    struct Add *ADD = (struct Add *)malloc(3 * sizeof(struct Add));
    ADD->ADbusy = (bool *)calloc(3, sizeof(bool));
    for (int i = 0; i < 3; i++)
    {
        ADD[i].ADop = (char *)calloc(6, sizeof(char));
        ADD[i].ADvj = (char *)calloc(6, sizeof(char));
        ADD[i].ADvk = (char *)calloc(6, sizeof(char));
        ADD[i].ADqj = (char *)calloc(6, sizeof(char));
        ADD[i].ADqk = (char *)calloc(6, sizeof(char));
        ADD[i].ADname = (char *)calloc(6, sizeof(char));
        //itoa(i + 1, str2, 10);
        sprintf(str, "%d", (i + 1));
        strcpy(ADD[i].ADname, "Add");
        strcat(ADD[i].ADname, str);
    }
    ADD->ADtime = (int *)calloc(3, sizeof(int));
    struct Mult *MULT = (struct Mult *)malloc(2 * sizeof(struct Mult));
    MULT->MUbusy = (bool *)calloc(3, sizeof(bool));
    for (int i = 0; i < 2; i++)
    {
        MULT[i].MUop = (char *)calloc(6, sizeof(char));
        MULT[i].MUvj = (char *)calloc(6, sizeof(char));
        MULT[i].MUvk = (char *)calloc(6, sizeof(char));
        MULT[i].MUqj = (char *)calloc(6, sizeof(char));
        MULT[i].MUqk = (char *)calloc(6, sizeof(char));
        MULT[i].MUname = (char *)calloc(6, sizeof(char));
        sprintf(str, "%d", (i + 1));
        strcpy(MULT[i].MUname, "Mult");
        strcat(MULT[i].MUname, str);
    }
    MULT->MUtime = (int *)calloc(2, sizeof(int));
    //�ŧi�p���O�һݪ��}�C

    struct Register *RE = (struct Register *)malloc(32 * sizeof(struct Register));
    RE->REfloat = (int *)calloc(16, sizeof(int));
    RE->REinteger = (int *)calloc(32, sizeof(int));
    //�ŧi��ƤίB�I�ƼȦs��
    for (int i = 0; i < 16; i++)
    {
        RE->REfloat[i] = 1;
        RE[i].REfloataddress = (char *)calloc(6, sizeof(char));
    }
    for (int i = 0; i < 32; i++)
    {
        RE[i].REintaddress = (char *)calloc(6, sizeof(char));
    }
    //��l�ƯB�I�ƼȦs�� �w�]�Ҭ�1
    RE->REinteger[1] = 16;
    //��l�ƾ�ƼȦs�� �w�]�Ҭ�0 ���FR1=16

    struct InstructionStatus *IS = (struct InstructionStatus *)malloc(AmountOfLine * sizeof(struct InstructionStatus));
    IS->ISissue = (int *)calloc((AmountOfLine), sizeof(int));
    IS->IScomp = (int *)calloc((AmountOfLine), sizeof(int));
    IS->ISresult = (int *)calloc((AmountOfLine), sizeof(int));
    //�ŧi���ܪ��A�һݰ}�C
    MakeChart(&AmountOfLine, DA, LBF, SBF, ADD, MULT, RE, IS);
    //while (clock != 50)
    while (flag != AmountOfLine + 1)
    {
        flag = 1;
        JudgmentAndOperation(&AmountOfLine, Memory, DA, LBF, SBF, ADD, MULT, RE, IS, RT);
        clock++;
        MakeChart(&AmountOfLine, DA, LBF, SBF, ADD, MULT, RE, IS);
        for (int i = 0; i < AmountOfLine; i++)
        {
            if (DA->Dflag[i])
            {
                flag++;
            }
        }
    }
    printf("\n%d\n", AmountOfLine);
    system("pause");
    return 0;
}
void LoadData(int *AOL, struct Data *_DA)
{
    FILE *File;
    File = fopen(TEST, "r");
    if (File)
    {
        for (int i = 0; i < (*AOL); i++)
        {
            fscanf(File, "%s ", _DA[i].Dop);
            if (strcmpi(_DA[i].Dop, "L.D") == 0 || strcmpi(_DA[i].Dop, "S.D") == 0)
            //if (strlen(_DA[i].Dop) == 3)
            {
                fscanf(File, "%s %s ", _DA[i].Di, _DA[i].Dj);
                // fscanf(File, "%*[^@]@%[^.]%s", _DA[i].Di, _DA[i].Dj);
            }
            else
            {
                fscanf(File, "%s %s %s ", _DA[i].Di, _DA[i].Dj, _DA[i].Dk);
            }
        }
    }
    else
    {
        printf("Open file faild!");
    }
}
void CalculationLine(int *AOL)
{
    char string;
    FILE *File;
    File = fopen(TEST, "r");
    while ((string = fgetc(File)) != EOF)
    {
        if (string == '\n')
        {
            (*AOL)++;
        }
    }
    fclose(File);
}
void MakeChart(int *AOL, struct Data *_DA, struct Buffer *_LBF, struct Buffer *_SBF, struct Add *_ADD, struct Mult *_MULT, struct Register *_RE, struct InstructionStatus *_IS)
{
    printf("clock:%d\n", clock);
    printf("Instruction status:\n");
    printf("Op\ti\tj\tk\tIssue\tComp\tResult\n");
    printf("\t\t\t\t�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < (*AOL); i++)
    {
        if (strcmpi(_DA[i].Dop, "L.D") == 0)
        {
            printf("%s\t%s\t%s\t\t�U%d\t%d\t%d\t�U\n", _DA[i].Dop, _DA[i].Di, _DA[i].Dj, _IS->ISissue[i], _IS->IScomp[i], _IS->ISresult[i]);
        }
        else
        {
            printf("%s\t%s\t%s\t%s\t�U%d\t%d\t%d\t�U\n", _DA[i].Dop, _DA[i].Di, _DA[i].Dj, _DA[i].Dk, _IS->ISissue[i], _IS->IScomp[i], _IS->ISresult[i]);
        }
    }
    printf("\t\t\t\t�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�XInstruction status

    printf("\tBusy\tAddress\n");
    printf("\t�z�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 2; i++)
    {
        printf("%s\t�U%d\t%s   �U\n", _LBF[i].BFname, _LBF->BFbusy[i], _LBF[i].BFaddress);
    }
    printf("\t�|�w�w�w�w�w�w�w�w�w�w�w�}\n");
    printf("\tBusy\tAddress\n");
    printf("\t�z�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 2; i++)
    {
        printf("%s\t�U%d\t%s   �U\n", _SBF[i].BFname, _SBF->BFbusy[i], _SBF[i].BFaddress);
    }
    printf("\t�|�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�XLoad/Buffers

    printf("Reservation Stations:\t\tS1\tS2\tRS\tRS\n");
    printf("Time\tName\tBusy\tOp\tVj\tVk\tQj\tQk\n");
    printf("\t\t�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d\t%s\t�U%d\t%s\t%s\t%s\t%s\t%s�U\n", _ADD->ADtime[i], _ADD[i].ADname, _ADD->ADbusy[i], _ADD[i].ADop, _ADD[i].ADvj, _ADD[i].ADvk, _ADD[i].ADqj, _ADD[i].ADqk);
    }
    for (int i = 0; i < 2; i++)
    {
        printf("%d\t%s\t�U%d\t%s\t%s\t%s\t%s\t%s�U\n", _MULT->MUtime[i], _MULT[i].MUname, _MULT->MUbusy[i], _MULT[i].MUop, _MULT[i].MUvj, _MULT[i].MUvk, _MULT[i].MUqj, _MULT[i].MUqk);
    }
    printf("\t\t�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�XReservation Stations

    printf("Register result status:\n");
    printf("Clock\t");
    for (int i = 0; i < 8; i++)
        printf("F%d\t", (i * 2));
    printf("\n\t�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    printf("%d\t", clock);
    for (int i = 0; i < 8; i++)
        printf("%s\t", _RE[i].REfloataddress);
    printf("\n\t�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    for (int i = 8; i < 16; i++)
        printf("F%d\t", (i * 2));
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 8; i < 16; i++)
        printf("%s\t", _RE[i].REfloataddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�X�B�I�ưO�����}

    for (int i = 0; i < 8; i++)
        printf("R%d\t", i);
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 8; i++)
        printf("%s\t", _RE[i].REintaddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");

    for (int i = 8; i < 16; i++)
        printf("R%d\t", i);
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 8; i < 16; i++)
        printf("%s\t", _RE[i].REintaddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");

    for (int i = 16; i < 24; i++)
        printf("R%d\t", i);
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 16; i < 24; i++)
        printf("%s\t", _RE[i].REintaddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    for (int i = 24; i < 32; i++)
        printf("R%d\t", i);
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 24; i < 32; i++)
        printf("%s\t", _RE[i].REintaddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�X��ưO�����}
}
void JudgmentAndOperation(int *AOL, int *MEM, struct Data *_DA, struct Buffer *_LBF, struct Buffer *_SBF, struct Add *_ADD, struct Mult *_MULT, struct Register *_RE, struct InstructionStatus *_IS, struct RecordTime *_RT)
{
    int Itemp = 0, Itemp2 = 0, Itemp3 = 0;
    //�Ĥ@��issue���P�_
    if (clock < (*AOL))
    {
        if (strcmpi(_DA[clock].Dop, "L.D") == 0) //2 cycles
        {
            sscanf(_DA[clock].Di, "F%d,", &Itemp); //���oload��m
            for (int i = 0; i < 2; i++)            //��X�Ū�buffer�N��Ʃ�J
            {
                if (!(_LBF->BFbusy[i]))
                {
                    _LBF[i].BFaddress = _DA[clock].Dj; //�bbuffer����Jj��m
                    _LBF->BFbusy[i] = true;
                    _RE[(Itemp / 2)].REfloataddress = _LBF[i].BFname; //�b�Ȧs����Jbuffer��m
                    _DA[clock].Dtag = _LBF[i].BFname;
                    _IS->ISissue[clock] = clock + 1;
                    _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
                    _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
                    printf("%s %d %d\n", _LBF[i].BFname, _RT->CompTime[clock], _RT->ResultTime[clock]);
                    printf("LDy\n");
                    break;
                }
            }
        }
        else if (strcmpi(_DA[clock].Dop, "S.D") == 0) //1 cycles
        {
            sscanf(_DA[clock].Di, "F%d,", &Itemp); //���ostore��m
            for (int i = 0; i < 2; i++)            //��X�Ū�buffer�N��Ʃ�J
            {
                if (!(_SBF->BFbusy[i]))
                {
                    _SBF[i].BFaddress = _DA[clock].Dj; //�bbuffer����Jj��m
                    _SBF->BFbusy[i] = true;
                    _DA[clock].Dtag = _SBF[i].BFname;
                    _IS->ISissue[clock] = clock + 1;
                    _RT->CompTime[clock] = clock + 2; //�]�m�����ɶ�
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _SBF[i].BFname; //�b�Ȧs����Jbuffer��m
                        _RT->ResultTime[clock] = clock + 4;               //�]�m��X�ɶ�
                        printf("%s %d %d\n", _SBF[i].BFname, _RT->CompTime[clock], _RT->ResultTime[clock]);
                        printf("SDy\n");
                        break;
                    }
                    break;
                }
            }
        }
        else if (strcmpi(_DA[clock].Dop, "ADD.D") == 0 || strcmpi(_DA[clock].Dop, "SUB.D") == 0) //2 cycles
        {
            sscanf(_DA[clock].Di, "F%d,", &Itemp);
            sscanf(_DA[clock].Dj, "F%d,", &Itemp2);
            sscanf(_DA[clock].Dk, "F%d", &Itemp3);
            for (int i = 0; i < 3; i++) //��mBusy�MOp
            {
                if (!(_ADD->ADbusy[i]))
                {
                    _ADD->ADbusy[i] = true;
                    _ADD[i].ADop = _DA[clock].Dop;
                    _DA[clock].Dtag = _ADD[i].ADname;
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _ADD[i].ADname;
                    }
                    if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0 && strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0)
                    {
                        _ADD[i].ADvj = _DA[clock].Dj;
                        _ADD[i].ADvk = _DA[clock].Dk;
                        _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
                        _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
                        printf("%s %d\n", _ADD[i].ADname, _RT->CompTime[clock]);
                        printf("ADDy\n");
                        break;
                    }
                    else
                    {
                        if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0)
                        {
                            _ADD[i].ADvj = _DA[clock].Dj;
                        }
                        else
                        {
                            _ADD[i].ADqj = _RE[(Itemp2 / 2)].REfloataddress;
                        }
                        if (strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0)
                        {
                            _ADD[i].ADvk = _DA[clock].Dk;
                        }
                        else
                        {
                            _ADD[i].ADqk = _RE[(Itemp3 / 2)].REfloataddress;
                        }
                        if (Itemp == Itemp2)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _ADD[i].ADqj = "";
                            _ADD[i].ADvj = _DA[clock].Dj;
                        }
                        if (Itemp == Itemp3)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _ADD[i].ADqk = "";
                            _ADD[i].ADvk = _DA[clock].Dk;
                        }
                        break;
                    }
                }
            }
            _IS->ISissue[clock] = clock + 1;
        }
        else if (strcmpi(_DA[clock].Dop, "MUL.D") == 0) //10 cycles
        {
            sscanf(_DA[clock].Di, "F%d,", &Itemp);
            sscanf(_DA[clock].Dj, "F%d,", &Itemp2);
            sscanf(_DA[clock].Dk, "F%d", &Itemp3);
            for (int i = 0; i < 2; i++) //��mBusy�MOp
            {
                if (!(_MULT->MUbusy[i]))
                {
                    _MULT->MUbusy[i] = true;
                    _MULT[i].MUop = _DA[clock].Dop;
                    _DA[clock].Dtag = _MULT[i].MUname;
                    //�Y��ӼȦs���ҨS���Aload�A�h�i�H�]�m�����ο�X�ɶ�
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _MULT[i].MUname;
                    }
                    if (strlen(_MULT[i].MUvk) != 0 && strlen(_MULT[i].MUvk) != 0)
                    {
                        _RT->CompTime[clock] = clock + 11;   //�]�m�����ɶ�
                        _RT->ResultTime[clock] = clock + 12; //�]�m��X�ɶ�
                        printf("%s %d %d\n", _MULT[i].MUname, _RT->CompTime[clock], _RT->ResultTime[clock]);
                        printf("MULy\n");
                        break;
                    }
                    else
                    {
                        if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                        {
                            _MULT[i].MUvj = _DA[clock].Dj;
                        }
                        else
                        {
                            _MULT[i].MUqj = _RE[(Itemp2 / 2)].REfloataddress;
                        }
                        if (strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                        {
                            _MULT[i].MUvk = _DA[clock].Dk;
                        }
                        else
                        {
                            _MULT[i].MUqk = _RE[(Itemp3 / 2)].REfloataddress;
                        }
                        if (Itemp == Itemp2)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _MULT[i].MUqj = "";
                            _MULT[i].MUvj = _DA[clock].Dj;
                        }
                        if (Itemp == Itemp3)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _MULT[i].MUqk = "";
                            _MULT[i].MUvk = _DA[clock].Dk;
                        }
                        break;
                    }
                }
            }
            _IS->ISissue[clock] = clock + 1;
        }
        else if (strcmpi(_DA[clock].Dop, "DIV.D") == 0) //40 cycles
        {
            sscanf(_DA[clock].Di, "F%d,", &Itemp);
            sscanf(_DA[clock].Dj, "F%d,", &Itemp2);
            sscanf(_DA[clock].Dk, "F%d", &Itemp3);
            for (int i = 0; i < 2; i++) //��mBusy�MOp
            {
                if (!(_MULT->MUbusy[i]))
                {
                    _MULT->MUbusy[i] = true;
                    _MULT[i].MUop = _DA[clock].Dop;
                    _DA[clock].Dtag = _MULT[i].MUname;
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _MULT[i].MUname;
                    }
                    if (strlen(_MULT[i].MUvk) != 0 && strlen(_MULT[i].MUvk) != 0)
                    {
                        _RT->CompTime[clock] = clock + 41;   //�]�m�����ɶ�
                        _RT->ResultTime[clock] = clock + 42; //�]�m��X�ɶ�
                        printf("%s %d %d\n", _MULT[i].MUname, _RT->CompTime[clock], _RT->ResultTime[clock]);
                        printf("MULy\n");
                        break;
                    }
                    else
                    {
                        if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                        {
                            _MULT[i].MUvj = _DA[clock].Dj;
                        }
                        else
                        {
                            _MULT[i].MUqj = _RE[(Itemp2 / 2)].REfloataddress;
                        }
                        if (strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                        {
                            _MULT[i].MUvk = _DA[clock].Dk;
                        }
                        else
                        {
                            _MULT[i].MUqk = _RE[(Itemp3 / 2)].REfloataddress;
                        }
                        if (Itemp == Itemp2)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _MULT[i].MUqj = "";
                            _MULT[i].MUvj = _DA[clock].Dj;
                        }
                        if (Itemp == Itemp3)
                        {
                            _RE[(Itemp / 2)].REfloataddress = "";
                            _MULT[i].MUqk = "";
                            _MULT[i].MUvk = _DA[clock].Dk;
                        }
                        break;
                    }
                }
            }
            _IS->ISissue[clock] = clock + 1;
        }
    }
    //�ˬd�����ɶ��O�_�w��F
    for (int i = 0; i < (*AOL); i++)
    {
        if (_RT->CompTime[i] > 0 || _RT->ResultTime[i] > 0)
        {
            if (_RT->CompTime[i] == clock + 1) //��s�����ɶ�
            {
                if (strcmpi(_DA[i].Dop, "L.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "S.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "ADD.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "SUB.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "MUL.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "DIV.D") == 0)
                {
                    _IS->IScomp[i] = clock + 1;
                }
                else
                    printf("Error");
            }
            if (_RT->ResultTime[i] == clock + 1) //��swrite back�ɶ�
            {
                if (strcmpi(_DA[i].Dop, "L.D") == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);              //���oload��m
                    sscanf(_DA[i].Dj, "%d(R%d)", &Itemp2, &Itemp3); //���o�����q�P�_�l��m
                    Itemp2 += _RE->REintaddress[Itemp3];
                    _RE->REfloat[(Itemp / 2)] = MEM[(Itemp2)]; //load data from memory
                    for (int j = 0; j < 2; j++)
                    {
                        if (strcmpi(_DA[i].Dtag, _LBF[j].BFname) == 0)
                        {
                            _LBF[j].BFaddress = "";
                            _LBF->BFbusy[j] = false;
                            _RE[(Itemp / 2)].REfloataddress = "";
                            break;
                        }
                    }
                    _DA->Dflag[i] = true;
                    _IS->ISresult[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "S.D") == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);                  //���oload��m
                    sscanf(_DA[i].Dj, "%d(R%d)", &Itemp2, &Itemp3);     //���o�����q�P�_�l��m
                    MEM[(Itemp2 + Itemp3)] = _RE->REfloat[(Itemp / 2)]; //store data from memory
                    for (int j = 0; j < 2; j++)
                    {
                        if (strcmpi(_DA[i].Dtag, _SBF[j].BFname) == 0)
                        {
                            _SBF[j].BFaddress = "";
                            _SBF->BFbusy[j] = false;
                            _RE[(Itemp / 2)].REfloataddress = "";
                            break;
                        }
                    }
                    _DA->Dflag[i] = true;
                    _IS->ISresult[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "ADD.D") == 0 || strcmpi(_DA[i].Dop, "SUB.D") == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);
                    for (int j = 0; j < 3; j++)
                    {
                        if (strcmpi(_DA[i].Dtag, _ADD[j].ADname) == 0)
                        {
                            _ADD->ADbusy[j] = 0;
                            _ADD[j].ADop = "";
                            _ADD[j].ADvj = "";
                            _ADD[j].ADvk = "";
                            _RE[(Itemp / 2)].REfloataddress = "";
                            break;
                        }
                    }
                    _DA->Dflag[i] = true;
                    _IS->ISresult[i] = clock + 1;
                }
                else if (strcmpi(_DA[i].Dop, "MUL.D") == 0 || strcmpi(_DA[i].Dop, "DIV.D") == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);
                    for (int j = 0; j < 2; j++)
                    {
                        if (strcmpi(_DA[i].Dtag, _MULT[j].MUname) == 0)
                        {
                            _MULT->MUbusy[j] = 0;
                            _MULT[j].MUop = "";
                            _MULT[j].MUvj = "";
                            _MULT[j].MUvk = "";
                            _RE[(Itemp / 2)].REfloataddress = "";
                            break;
                        }
                    }
                    _DA->Dflag[i] = true;
                    _IS->ISresult[i] = clock + 1;
                }
                else
                    printf("Error");
            }
        }
    }
    //�ˬd�S�������ο�X�ɶ��B�⤸
    for (int j = 0; j < 3; j++) //Add
    {
        if (_ADD->ADbusy[j])
        {
            for (int i = 0; i < (*AOL); i++)
            {
                if (strcmpi(_DA[i].Dtag, _ADD[j].ADname) == 0 && _RT->CompTime[i] == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);
                    sscanf(_DA[i].Dj, "F%d,", &Itemp2);
                    sscanf(_DA[i].Dk, "F%d", &Itemp3);

                    if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0)
                    {
                        _ADD[j].ADvj = _DA[i].Dj;
                        _ADD[j].ADqj = "";
                    }
                    if (strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                    {
                        _ADD[j].ADvk = _DA[i].Dk;
                        _ADD[j].ADqk = "";
                    }
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                    {
                        _RE[(Itemp / 2)].REfloataddress = _ADD[i].ADname;
                    }
                    if (Itemp == Itemp2)
                    {
                        _RE[(Itemp / 2)].REfloataddress = "";
                        _ADD[j].ADqj = "";
                        _ADD[j].ADvj = _DA[i].Dj;
                    }
                    if (Itemp == Itemp3)
                    {
                        _RE[(Itemp / 2)].REfloataddress = "";
                        _ADD[j].ADqk = "";
                        _ADD[j].ADvk = _DA[i].Dk;
                    }
                    if (strlen(_ADD[j].ADvj) != 0 && strlen(_ADD[j].ADvk) != 0)
                    {
                        _RT->CompTime[i] = clock + 3;   //�]�m�����ɶ�
                        _RT->ResultTime[i] = clock + 4; //�]�m��X�ɶ�
                        printf("%s %d %d\n", _ADD[j].ADname, _RT->CompTime[i], _RT->ResultTime[i]);
                    }
                }
            }
        }
    }
    for (int j = 0; j < 2; j++) //Mult an store
    {
        if (_MULT->MUbusy[j])
        {
            for (int i = 0; i < (*AOL); i++)
            {
                if (strcmpi(_DA[i].Dtag, _MULT[j].MUname) == 0 && _RT->CompTime[i] == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp);
                    sscanf(_DA[i].Dj, "F%d,", &Itemp2);
                    sscanf(_DA[i].Dk, "F%d", &Itemp3);
                    if (strlen(_RE[(Itemp2 / 2)].REfloataddress) == 0)
                    {
                        _MULT[j].MUvj = _DA[i].Dj;
                        _MULT[j].MUqj = "";
                    }
                    if (strlen(_RE[(Itemp3 / 2)].REfloataddress) == 0) //�T�{�ӼȦs���O�_�Aload
                    {
                        _MULT[j].MUvk = _DA[i].Dk;
                        _MULT[j].MUqk = "";
                    }
                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _MULT[j].MUname;
                    }
                    if (Itemp == Itemp2)
                    {
                        _RE[(Itemp / 2)].REfloataddress = "";
                        _MULT[j].MUqj = "";
                        _MULT[j].MUvj = _DA[i].Dj;
                    }
                    if (Itemp == Itemp3)
                    {
                        _RE[(Itemp / 2)].REfloataddress = "";
                        _MULT[j].MUqk = "";
                        _MULT[j].MUvk = _DA[i].Dk;
                    }
                    if (strlen(_MULT[j].MUvj) != 0 && strlen(_MULT[j].MUvk) != 0)
                    {
                        if (strcmpi(_MULT[j].MUop, "MUL.D") == 0)
                        {
                            _RT->CompTime[i] = clock + 11;   //�]�m�����ɶ�
                            _RT->ResultTime[i] = clock + 12; //�]�m��X�ɶ�
                            printf("%s %d %d\n", _MULT[j].MUname, _RT->CompTime[i], _RT->ResultTime[i]);
                        }
                        else if (strcmpi(_MULT[j].MUop, "DIV.D") == 0)
                        {
                            _RT->CompTime[i] = clock + 41;   //�]�m�����ɶ�
                            _RT->ResultTime[i] = clock + 42; //�]�m��X�ɶ�
                            printf("%s %d %d\n", _MULT[j].MUname, _RT->CompTime[i], _RT->ResultTime[i]);
                        }
                    }
                }
            }
        }
        if (_SBF->BFbusy[j])
        {
            for (int i = 0; i < (*AOL); i++)
            {
                if (strcmpi(_DA[i].Dtag, _SBF[j].BFname) == 0 && _RT->ResultTime[i] == 0)
                {
                    sscanf(_DA[i].Di, "F%d,", &Itemp); //���oload��m

                    if (strlen(_RE[(Itemp / 2)].REfloataddress) == 0)
                    {
                        _RE[(Itemp / 2)].REfloataddress = _SBF[j].BFname; //�b�Ȧs����Jbuffer��m
                        _RT->ResultTime[i] = clock + 2;                   //�]�m��X�ɶ�
                        printf("%s %d %d\n", _SBF[j].BFname, _RT->CompTime[i], _RT->ResultTime[i]);
                        printf("SDy2\n");
                    }
                }
            }
        }
    }
}