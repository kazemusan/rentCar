#include "log_in.h"
#include "ui_log_in.h"

/*
 * This is the Login Page
 * As the start interface allows user login
 * Also connect to sign up and Admin interfaces
 *
 */

Log_in::Log_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Log in");
    ui->userNameBtn->setFocus();  //set the cursor on user name area

    ui->logInSuccessful->setVisible(false);

    // operator new pages of sign in, main screen and adminstrator
    signIn = new Sign_In;
    signIn->hide();
    mainPage = new MainScreen;
    mainPage->hide();
    admin = new adminstrator;
    admin->hide();

    /*
     * Connect to sign in page and back
     * The login page provides an interface
     * to back to login from the main and sign up pages
     *
     */
    connect(ui->SignInBtn, &clickableLabel::clicked, this, [=](){
        // When the user click sign up button
        // The sign up page shows
        // Log in page hide
        signIn->show();
        this->hide();
    });

    connect(signIn, &Sign_In::backLogIn, this, [=](){
        cleanLineEdit();
        signIn->hide();
        this->show();
    });

    connect(admin, &adminstrator::backToLogIn, this, [=](){
        //        admin->hide();
        //        this->show();
        QTimer::singleShot(500, this, [=](){
            admin->hide();
            this->show();
        });
    });

        connect(mainPage, &MainScreen::backToLogIn, this, [=](){
            QTimer::singleShot(500, this, [=](){
                mainPage->hide();
                this->show();
            });
        });
}

// this method is for inserting the background image
void Log_in::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);

}

void Log_in::on_LogBtn_clicked()
{
    connectDatabase();
    matchDatabase();
}


void Log_in::connectDatabase()
{
    qDebug()<<"connect succeed";
}

void Log_in::matchDatabase()
{
    QString userName = ui->userNameBtn->text();
    QString password = ui->passwordBtn->text();
    qDebug()<<"username:"<<userName<<"\tpassword:"<<password;
    qDebug()<<"match succeed\n";

    //adminShow();
    mainScreenShow();
}

void Log_in::adminShow()
{
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
        QTimer::singleShot(1000, this, [=](){
            qDebug()<<"admin show\n";
            this->hide();
            admin->show();
            ui->logInSuccessful->setVisible(false);
            qDebug()<<"admin showed\n";
        });
    });
}

void Log_in::mainScreenShow()
{
    QString userName = ui->userNameBtn->text();

    //Pause 0.5 second when login successed for better user experience
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
    });

    QTimer::singleShot(1500, this, [=](){
        // username of main page is inherited to here
        mainPage->usersNames = userName;
        this->hide();
        mainPage->show();

        //declear in mainPage, implement in here.
        //Otherwise the obtained data will be covered
        mainPage->init();
        ui->logInSuccessful->setVisible(false);
        cleanLineEdit();
    });

}

void Log_in::cleanLineEdit()
{
    ui->userNameBtn->clear();
    ui->passwordBtn->clear();

}

Log_in::~Log_in()
{
    delete ui;
}
