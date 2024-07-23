#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTime>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dot_product_btn_clicked()
{
    interface->LhtDotProductFloat(testVec1,testVec2,11,testVecResult,1);

    ui->textEdit->append(QString::number(testVecResult[0]));

}


void MainWindow::on_add_btn_clicked()
{
    interface->LhtAddFloat(testVec1,testVec2,11,testVecResult,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_sub_btn_clicked()
{
    interface->LhtSubFloat(testVec1,testVec2,11,testVecResult,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_mul_btn_clicked()
{
    interface->LhtMulCFloat(testVec1,5,11,testVecResult,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_max_btn_clicked()
{
    interface->LhtMaxFloat(testVec1,11,testVecResult,1);
    for(int i = 0 ; i < 1 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_min_btn_clicked()
{
    interface->LhtMinFloat(testVec1,11,testVecResult,1);
    for(int i = 0 ; i < 1 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_mean_btn_clicked()
{
    interface->LhtMeanFloat(testVec1,11,testVecResult,1);
    for(int i = 0 ; i < 1 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_sort_btn_clicked()
{
    interface->LhtSortFloat(testVec1,11,testVecResult,ui->checkBox->isChecked(),1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_filp_btn_clicked()
{
    interface->LhtFlip(testVec1,testVecResult,11,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_init_btn_clicked()
{
    interface = new ComputingInterface;
}


void MainWindow::on_vec_mul_btn_clicked()
{
    interface->LhtMulFloat(testVec1,testVec2,11,testVecResult,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}


void MainWindow::on_max2_btn_clicked()
{
    interface->LhtNormInfFloat(testVec1,11,testVecResult,1);
    for(int i = 0 ; i < 1 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}

void MainWindow::on_fft_init_btn_clicked()
{
    auto size = 16384 * 16;
    interface->LhtFftInitFloat(size);
}

void MainWindow::on_fft_btn_clicked()
{
    auto size = 16384 * 16;
    float * in1 = new float[size]{-1};
    float * in2 = new float[size]{-2};
    float * result = new float[size];
    QFile file("E:/git/lht-qt-plugins/LhtIPPS/1.AcceleratedComputing/IPPSAcceleratedComputing/debug/re.txt");
    QFile file1("E:/git/lht-qt-plugins/LhtIPPS/1.AcceleratedComputing/IPPSAcceleratedComputing/debug/im.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    file1.open(QIODevice::ReadOnly|QIODevice::Text);
    for (int i = 0; i < size  ;i++) {
        in1[i] = file.readLine().toFloat();
    }
    for (int i = 0; i < size ;i++) {
        in2[i] = file1.readLine().toFloat();
    }
    QTime t;
    t.start();
    for(int i = 0 ; i < 16 ; i++){
        interface->LhtFftFloat(in1,in2,size,result);
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    delete []in1;
    delete []in2;
    delete []result;
}

void MainWindow::on_dft_init_btn_clicked()
{
    auto size = 16384;
    interface->LhtDftInitFloat(size);
}

void MainWindow::on_dft_btn_clicked()
{
    auto size = 16384;
    float * in1 = new float[size];
    float * in2 = new float[size];
    float * result1 = new float[size];
    float * result2 = new float[size];

    interface->LhtDftFloat(in1,in2,size,result1,result2,1);
    delete []in1;
    delete []in2;
    delete []result1;
    delete []result2;
}

void MainWindow::on_normalize_btn_clicked()
{
    //1.找到绝对值最大值
    interface->LhtNormInfFloat(testVec1,11,testVecResult,1);

    //2.所有数除以他
    auto max = testVecResult[0];
    ui->textEdit->append("Max :"+QString::number(max));
    interface->LhtNormalizeFloat(testVec1,11,testVecResult,0,max,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}



void MainWindow::on_power_btn_clicked()
{
    interface->LhtPowerSpectrFloat(testVec1,testVec2,11,testVecResult,1);
    for(int i = 0 ; i < 11 ; i++){
        ui->textEdit->append(QString::number(testVecResult[i]));
    }
}

void MainWindow::on_resample_init_btn_clicked()
{
    //假设下抽两倍  上采样1  下采样2

    float taps[128]{ -0.000288425418546259,-0.000149613700895877,0.000425799840009783,-0.000181741786873686,-0.000327147797888032,0.000478605814009484,
    -1.87230062930546e-05,-0.000549965503347957,0.000486995852459927,0.000250463924892394,-0.000803708719429460,0.000378882359349824,
    0.000657889811409452,-0.00102231662396788,6.74442413324198e-05,0.00118706691534464,-0.00108928508888713,-0.000514523840161149,0.00175037793374656,
    -0.000859232063365237,-0.00137474175490462,0.00218415844456354, -0.000197823584694360, -0.00242724158067863,0.00226729951202306,0.000967433289768777,
    -0.00347523789871615,0.00176367381108958,0.00259714704348053,-0.00421963228068895,0.000482446912655895,0.00450380008441333,-0.00429627071846574,
    -0.00165495553982476,0.00634040871628770,-0.00333819442607227,-0.00455521851421134,0.00761985963021721,-0.00105242112067582,-0.00791385948910419,
    0.00776263575930902,0.00270405699332606,-0.0112037869505664,0.00616059433676466,0.00786604035147338,-0.0136881404611686,0.00223192330309019,
    0.0141344836314940,-0.0144336904347710,-0.00457853007425256,0.0209925524546433,-0.0122554320954136,-0.0149568092047350,0.0277642773617169,
    -0.00537241467130189,-0.0303747055051943,0.0337077784326489,0.0101934903986004, -0.0559939458685150,	0.0381273573264599,	0.0509437727654211,
    -0.124318964129941,0.0404840960686762,0.530003886532873,0.530003886532873,	0.0404840960686762, -0.124318964129941,0.0509437727654211,0.0381273573264599,
    -0.0559939458685150,0.0101934903986004,0.0337077784326489, -0.0303747055051943, -0.00537241467130189,0.0277642773617169, -0.0149568092047350,
    -0.0122554320954136,0.0209925524546433, -0.00457853007425256, -0.0144336904347710,0.0141344836314940,0.00223192330309019, -0.0136881404611686,
    0.00786604035147338,0.00616059433676466, -0.0112037869505664,0.00270405699332606,0.00776263575930902, -0.00791385948910419, -0.00105242112067582,
    0.00761985963021721, -0.00455521851421134, -0.00333819442607227,0.00634040871628770, -0.00165495553982476, -0.00429627071846574,
    0.00450380008441333,0.000482446912655895, -0.00421963228068895,0.00259714704348053,0.00176367381108958, -0.00347523789871615,	0.000967433289768777,
    0.00226729951202306, -0.00242724158067863, -0.000197823584694360,	0.00218415844456354, -0.00137474175490462, -0.000859232063365237,	0.00175037793374656,
    -0.000514523840161149, -0.00108928508888713,	0.00118706691534464,6.74442413324198e-05,-0.00102231662396788,	0.000657889811409452,	0.000378882359349824,
    -0.000803708719429460,	0.000250463924892394,	0.000486995852459927, -0.000549965503347957, -1.87230062930546e-05,	0.000478605814009484, -0.000327147797888032,
    -0.000181741786873686,	0.000425799840009783, -0.000149613700895877, -0.000288425418546259 };
    // 使用std::fill初始化数组
    //std::fill_n(taps, 128, 1.f);
    interface->LhtResampleInit(96000,200000);
}
#include <QFile>
void MainWindow::on_resample_btn_clicked()
{

    auto size = 16384;
    float * in1 = new float[size * 2]{0};
    float* in2 = new float[size * 2]{ 0 };
    QFile file("./re.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    for (int i = 0; i < size * 2 ;i++) {
        in1[i] = file.readLine().toFloat();
    }
    QFile file1("./im.txt");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    for (int i = 0; i < size * 2;i++) {
        in2[i] = file1.readLine().toFloat();
    }
    // 使用std::fill初始化数组
    //std::fill_n(in1, size * 2, 1.5f);
    float * result1 = new float[size * 20];
    float * result2 = new float[size * 20];
    int retLen;
    interface->LhtResample(in1, result1, size * 2, retLen);
    interface->LhtResample(in2, result2, size * 2, retLen);
    FILE* fp3;
    fp3 = fopen("./resample_re.txt", "w");
    for (int m = 0; m < size; m++)
        {
        fprintf(fp3, "%f\n", result1[m]);

        }
    fclose(fp3);
    FILE* fp4;
    fp4 = fopen("./resample_im.txt", "w");
    for (int m = 0; m < size; m++)
        {
        fprintf(fp4, "%f\n", result2[m]);

    }
    fclose(fp4);
    //auto str = interface->arrayToString(result1,retLen);
    //ui->textEdit->append(str);

    delete []in1;
    delete []result1;
    delete []in2;
    delete []result2;
}

void MainWindow::on_filter_lp_init_btn_clicked()
{
    float taps[128]{ -0.000288425418546259,- 0.000149613700895877,0.000425799840009783,-0.000181741786873686,-0.000327147797888032,0.000478605814009484,
        -1.87230062930546e-05,- 0.000549965503347957,0.000486995852459927,0.000250463924892394,-0.000803708719429460,0.000378882359349824,
        0.000657889811409452,-0.00102231662396788,6.74442413324198e-05,0.00118706691534464,-0.00108928508888713,-0.000514523840161149,0.00175037793374656,
        - 0.000859232063365237,- 0.00137474175490462,0.00218415844456354, - 0.000197823584694360, - 0.00242724158067863,0.00226729951202306,0.000967433289768777, 
        - 0.00347523789871615,0.00176367381108958,0.00259714704348053,- 0.00421963228068895,0.000482446912655895,0.00450380008441333,- 0.00429627071846574, 
        - 0.00165495553982476,0.00634040871628770,- 0.00333819442607227,- 0.00455521851421134,0.00761985963021721,- 0.00105242112067582,- 0.00791385948910419,
        0.00776263575930902,0.00270405699332606,- 0.0112037869505664,0.00616059433676466,0.00786604035147338,- 0.0136881404611686,0.00223192330309019,
        0.0141344836314940,- 0.0144336904347710,- 0.00457853007425256,0.0209925524546433,- 0.0122554320954136,- 0.0149568092047350,0.0277642773617169,
        - 0.00537241467130189,- 0.0303747055051943,0.0337077784326489,0.0101934903986004, - 0.0559939458685150,	0.0381273573264599,	0.0509437727654211, 
        - 0.124318964129941,0.0404840960686762,0.530003886532873,0.530003886532873,	0.0404840960686762, - 0.124318964129941,0.0509437727654211,0.0381273573264599,
        - 0.0559939458685150,0.0101934903986004,0.0337077784326489, - 0.0303747055051943, - 0.00537241467130189,0.0277642773617169, - 0.0149568092047350,
        - 0.0122554320954136,0.0209925524546433, - 0.00457853007425256, - 0.0144336904347710,0.0141344836314940,0.00223192330309019, - 0.0136881404611686,
        0.00786604035147338,0.00616059433676466, - 0.0112037869505664,0.00270405699332606,0.00776263575930902, - 0.00791385948910419, - 0.00105242112067582,
        0.00761985963021721, - 0.00455521851421134, - 0.00333819442607227,0.00634040871628770, - 0.00165495553982476, - 0.00429627071846574,
        0.00450380008441333,0.000482446912655895, - 0.00421963228068895,0.00259714704348053,0.00176367381108958, - 0.00347523789871615,	0.000967433289768777,
        0.00226729951202306, - 0.00242724158067863, - 0.000197823584694360,	0.00218415844456354, - 0.00137474175490462, - 0.000859232063365237,	0.00175037793374656,
        - 0.000514523840161149, - 0.00108928508888713,	0.00118706691534464,6.74442413324198e-05,- 0.00102231662396788,	0.000657889811409452,	0.000378882359349824,
        - 0.000803708719429460,	0.000250463924892394,	0.000486995852459927, - 0.000549965503347957, - 1.87230062930546e-05,	0.000478605814009484, - 0.000327147797888032,
        - 0.000181741786873686,	0.000425799840009783, - 0.000149613700895877, - 0.000288425418546259 };
    // 使用std::fill初始化数组
    //std::fill_n(taps, 128, 1.f);
    interface->LhtFirInitFloatLp(taps,128);
}

void MainWindow::on_filter_lp_btn_clicked()
{
    auto size = 16384;
    float * in1 = new float[size ]{0};
    //std::fill_n(in1, size, 2.f);
    FILE* fp1;
    fp1 = fopen("./re.txt", "r");
    for (int m = 0; m < size; m++)
    {
        fscanf_s(fp1, "%f", &in1[m]);
    }
    fclose(fp1);
    float * result1 = new float[size];
    interface->LhtFirFloatLp(in1,result1,size);
    //auto str = interface->arrayToString(result1,size);
    //ui->textEdit->append(str);
    delete []in1;
    delete []result1;
}

