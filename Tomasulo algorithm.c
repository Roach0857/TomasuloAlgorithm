#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void strchrn(char *dest, const char *src, char b, char e)
{
    char *m = strchr(src, b) + 1;
    char *n = strchr(src, e);
    int len = strlen(m) - strlen(n);
    strncpy(dest, m, len);
    dest[len] = '\0';
}
struct Data
{
    char *Dop;
    char *Di;
    char *Dj;
    char *Dk;
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
void MakeChart(int *, struct Data *, struct Buffer *, struct Add *, struct Mult *, struct Register *, struct InstructionStatus *);
void JudgmentAndOperation(int *, int *, struct Data *, struct Buffer *, struct Add *, struct Mult *, struct Register *, struct InstructionStatus *, struct RecordTime *);
int main(void)
{
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
    }
    //�ŧi���ɤ��e
    LoadData(&AmountOfLine, DA);
    //Ū�����ɸ��

    struct Buffer *BF = (struct Buffer *)calloc(3, sizeof(struct Buffer));
    BF->BFbusy = (bool *)calloc(3, sizeof(bool));
    BF->BFvalue = (int *)calloc(3, sizeof(int));
    char *str = (char *)malloc(1 * sizeof(char));
    for (int i = 0; i < 3; i++)
    {
        BF[i].BFaddress = (char *)calloc(6, sizeof(char));
        BF[i].BFname = (char *)calloc(6, sizeof(char));
        itoa(i + 1, str, 10);
        strcpy(BF[i].BFname, "load");
        strcat(BF[i].BFname, str);
    }
    //�ŧibuffer��3��load

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
        ADD[i].ADop = (char *)calloc(5, sizeof(char));
        ADD[i].ADvj = (char *)calloc(5, sizeof(char));
        ADD[i].ADvk = (char *)calloc(5, sizeof(char));
        ADD[i].ADqj = (char *)calloc(5, sizeof(char));
        ADD[i].ADqk = (char *)calloc(5, sizeof(char));
    }
    ADD->ADtime = (int *)calloc(3, sizeof(int));
    struct Mult *MULT = (struct Mult *)malloc(2 * sizeof(struct Mult));
    MULT->MUbusy = (bool *)calloc(3, sizeof(bool));
    for (int i = 0; i < 2; i++)
    {
        MULT[i].MUop = (char *)calloc(5, sizeof(char));
        MULT[i].MUvj = (char *)calloc(5, sizeof(char));
        MULT[i].MUvk = (char *)calloc(5, sizeof(char));
        MULT[i].MUqj = (char *)calloc(5, sizeof(char));
        MULT[i].MUqk = (char *)calloc(5, sizeof(char));
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
    MakeChart(&AmountOfLine, DA, BF, ADD, MULT, RE, IS);
    while (clock != AmountOfLine)
    {
        JudgmentAndOperation(&AmountOfLine, Memory, DA, BF, ADD, MULT, RE, IS, RT);
        MakeChart(&AmountOfLine, DA, BF, ADD, MULT, RE, IS);
    }

    printf("\n%d\n", AmountOfLine);
    system("pause");
    return 0;
}
void LoadData(int *AOL, struct Data *_DA)
{
    FILE *File;
    File = fopen("test3.txt", "r");
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
    File = fopen("test3.txt", "r");
    while ((string = fgetc(File)) != EOF)
    {
        if (string == '\n')
        {
            (*AOL)++;
        }
    }
    fclose(File);
}
void MakeChart(int *AOL, struct Data *_DA, struct Buffer *_BF, struct Add *_ADD, struct Mult *_MULT, struct Register *_RE, struct InstructionStatus *_IS)
{
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

    for (int i = 0; i < 3; i++)
    {
        printf("%s\t�U%d\t%s   �U\n", _BF[i].BFname, _BF->BFbusy[i], _BF[i].BFaddress);
    }
    printf("\t�|�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�XLoad/Buffers

    printf("Reservation Stations:\t\tS1\tS2\tRS\tRS\n");
    printf("Time\tName\tBusy\tOp\tVj\tVk\tQj\tQk\n");
    printf("\t\t�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\t%d\t�U%d\t%s\t%s\t%s\t%s\t%s�U\n", _ADD->ADtime[i], _ADD->ADbusy[i], _ADD[i].ADop, _ADD[i].ADvj, _ADD[i].ADvk, _ADD[i].ADqj, _ADD[i].ADqk);
    }
    for (int i = 0; i < 2; i++)
    {
        printf("\t%d\t�U%d\t%s\t%s\t%s\t%s\t%s�U\n", _MULT->MUtime[i], _MULT->MUbusy[i], _MULT[i].MUop, _MULT[i].MUvj, _MULT[i].MUvk, _MULT[i].MUqj, _MULT[i].MUqk);
    }
    printf("\t\t�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�XReservation Stations

    printf("Register result status:\n");
    printf("Clock\t\t");
    for (int i = 0; i < 16; i++)
        printf("F%d\t", (i * 2));
    printf("\n\t\t�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    printf("%d\t\t", clock);
    for (int i = 0; i < 16; i++)
        printf("%s\t", _RE[i].REfloataddress);
    printf("\n\t\t�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�X�B�I�ưO�����}
    for (int i = 0; i < 32; i++)
        printf("R%d\t", i);
    printf("\n�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{\n");
    for (int i = 0; i < 32; i++)
        printf("%s\t", _RE[i].REintaddress);
    printf("\n�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}\n");
    //�e�X��ưO�����}
    printf("clock:%d\n", clock);
}
void JudgmentAndOperation(int *AOL, int *MEM, struct Data *_DA, struct Buffer *_BF, struct Add *_ADD, struct Mult *_MULT, struct Register *_RE, struct InstructionStatus *_IS, struct RecordTime *_RT)
{
    char Ctemp[2] = {0}, Ctemp2[2] = {0}, Ctemp3[2] = {0};
    int Itemp = 0, Itemp2 = 0, Itemp3 = 0;
    if (strcmpi(_DA[clock].Dop, "L.D") == 0) //2 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        strchrn(Ctemp, _DA[clock].Di, 'F', ','); //���oload��m
        Itemp = atoi(Ctemp);
        for (int i = 0; i < 3; i++) //��X�Ū�buffer�N��Ʃ�J
        {
            if (!(_BF->BFbusy[i]))
            {
                _RE[(Itemp / 2)].REfloataddress = _BF[i].BFname; //�b�Ȧs����Jbuffer��m
                _BF[i].BFaddress = _DA[clock].Dj;                //�bbuffer����Jj��m
                _BF->BFbusy[i] = true;
                break;
            }
        }
        _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
        clock++;
    }
    else if (strcmpi(_DA[clock].Dop, "S.D") == 0) //2 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
        clock++;
    }
    else if (strcmpi(_DA[clock].Dop, "ADD.D") == 0) //2 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
        clock++;
    }
    else if (strcmpi(_DA[clock].Dop, "SUB.D") == 0) //2 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        _RT->CompTime[clock] = clock + 3;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 4; //�]�m��X�ɶ�
        clock++;
    }
    else if (strcmpi(_DA[clock].Dop, "MUL.D") == 0) //10 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        _RT->CompTime[clock] = clock + 11;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 12; //�]�m��X�ɶ�
        clock++;
    }
    else if (strcmpi(_DA[clock].Dop, "DIV.D") == 0) //40 cycles
    {
        _IS->ISissue[clock] = clock + 1;
        _RT->CompTime[clock] = clock + 11;   //�]�m�����ɶ�
        _RT->ResultTime[clock] = clock + 12; //�]�m��X�ɶ�
        clock++;
    }

    for (int i = 0; i < (*AOL); i++) //�ˬd�����ɶ��O�_�w��F
    {
        if (_RT->CompTime[i] == clock) //��s�����ɶ�
        {
            if (strcmpi(_DA[i].Dop, "L.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "S.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "ADD.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "SUB.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "MUL.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "DIV.D") == 0)
            {
                _IS->IScomp[i] = clock;
                _RT->CompTime[i] = 0;
            }
            else
                printf("Error");
        }
        else if (_RT->ResultTime[i] == clock) //��swrite back�ɶ�
        {
            if (strcmpi(_DA[i].Dop, "L.D") == 0)
            {
                strchrn(Ctemp, _DA[i].Di, 'F', ',');  //���oload��m
                strchrn(Ctemp2, _DA[i].Dj, ' ', '('); //���o������m
                strchrn(Ctemp3, _DA[i].Dj, 'R', ')'); //���o�_�l��m
                Itemp = atoi(Ctemp);
                Itemp2 = atoi(Ctemp2);
                Itemp3 = atoi(Ctemp3);
                Itemp2 += _RE->REintaddress[Itemp3];
                _RE->REfloat[(Itemp / 2)] = MEM[(Itemp2)]; //load data from memory
                for (int j = 0; j < 3; j++)
                {
                    if (strcmpi(_DA[i].Dj, _BF[j].BFaddress) == 0)
                    {
                        _BF[j].BFaddress = "";
                        _BF->BFbusy[j] = false;
                        for (int k = 0; k < 15; k++)
                        {
                            if (_BF[j].BFname == _RE[k].REfloataddress)
                            {
                                _RE[k].REfloataddress = "";
                                break;
                            }
                        }
                        break;
                    }
                }
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "S.D") == 0)
            {
                // strchrn(Ctemp, _DA[i].Di, 'F', ','); //���ostore��m
                // Itemp = atoi(Ctemp);
                // strchrn(Ctemp2, _DA[i].Dj, ' ', '('); //���o������m
                // Itemp2 = atoi(Ctemp2);
                // strchrn(Ctemp3, _DA[i].Dj, 'R', ')'); //���o�_�l��m
                // Itemp3 = atoi(Ctemp3);
                // MEM[(Itemp2 + Itemp3)] = _RE->REfloat[(Itemp / 2)];
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "ADD.D") == 0)
            {
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "SUB.D") == 0)
            {
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "MUL.D") == 0)
            {
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else if (strcmpi(_DA[i].Dop, "DIV.D") == 0)
            {
                _IS->ISresult[i] = clock;
                _RT->ResultTime[i] = 0;
            }
            else
                printf("Error");
        }
    }
}