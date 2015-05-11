/**
 * @file MainWindow.h
 * @brief Main window for the Clusterer GUI
 */

// standard headers
#include <limits>

// Own headers
#include "../include/MainWindow.h"
#include "../include/SettingsDialog.h"
#include "../include/PopulationMember.hpp"
#include "../include/IntegerVectorEncoding.hpp"

// External headers
#include <QMessageBox>
#include <QFileDialog>

// Generated headers
#include "ui_MainWindow.h"
#include "../include/GlobalBackendController.hpp"
#include "../include/GlobalFileLogger.hpp"



namespace clusterer
{

namespace frontend
{


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateFrontend()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrontend()
{
    std::pair<clb::PopulationMember<clb::IntegerVectorEncoding, double>, uint64_t> output;
    std::vector<std::pair<clb::PopulationMember<clb::IntegerVectorEncoding, double>, uint64_t>> vector;
    while (clb::GlobalBackendController::instance()->getOutQueue()->popNonWaiting(output))
    {
        vector.push_back(output);
    }

    if (!vector.empty())
    {
        bool exitFlag = false;
        std::vector<std::pair<uint64_t, double>> fitnessVec;
        fitnessVec.reserve(vector.size());
        for (auto& e : vector)
        {
            if (std::numeric_limits<uint64_t>::max() - std::numeric_limits<uint64_t>::epsilon() <= e.second)
            {
                // algo stopped
                exitFlag = true;
                continue;
            }
            fitnessVec.push_back(std::make_pair(e.second, e.first.fitnessValue));
        }
        ui->fitnessPlotter->replotFitness(fitnessVec);

        if (exitFlag == true && vector.size() > 1)
        {
            ui->nodePlotter->replotSolution(vector[vector.size() - 2].first.populationEncoding);
        }
        else
        {
            ui->nodePlotter->replotSolution(vector[vector.size() - 1].first.populationEncoding);
        }
    }
}

void MainWindow::showAlert(const QString& title, const QString& text)
{
    QMessageBox::information(this, title, text);
}

void MainWindow::on_pushButton_clicked()
{
    //Start button
    // @todo put check condition function into controller and call it here and check
    if (clb::GlobalBackendController::instance()->runAlgorithm(true))
    {
        timer.start(16);
        this->showAlert("Info", "Started the algorithm");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Could not start the algorithm as you need to load a Graph first.");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop button
    clb::GlobalBackendController::instance()->stopAlgorithm();
    this->showAlert("Alert", "Stop");
}

void MainWindow::on_pushButton_2_clicked()
{
    clb::GlobalBackendController::instance()->stopAlgorithm();
    this->showAlert("Alert", "Pause");
}

void MainWindow::on_pushButton_3_clicked()
{
    clb::GlobalBackendController::instance()->runAlgorithm(false);
    this->showAlert("Alert", "Resume");
}

void MainWindow::on_actionSave_Settings_2_triggered()
{
    // Save settings
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Settings"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->saveConfiguration(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Settings Success", "Successfully saved settings");
        }
        else
        {
            QMessageBox::critical(this, "Save Settings failed", "Failed saving settings.");
        }
    }
}

void MainWindow::on_actionLoad_Settings_2_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Settings File"),
                   ".",
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->loadConfiguration(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Settings Success", "Successfully loaded settings");
        }
        else
        {
            QMessageBox::critical(this, "Load Settings failed", "The file you selected is not a valid configuration file");
        }
    }
}

void MainWindow::on_actionSave_Graph_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Graph"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->saveGraphToFile(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Graph Success", "Successfully saved graph to file.");
        }
        else
        {
            QMessageBox::critical(this, "Save Graph failed", "Unable to save graph");
        }
    }
}

void MainWindow::on_actionZachary_format_triggered()
{
    // Load Zachary Format
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Zachary Karate Club Graph"),
                   ".",
                   tr("All Files (*)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->loadGraphTypeVertexPairWeight(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Graph Success", "Successfully loaded a vertex-pair-weight type graph.");
            ui->nodePlotter->initGraph();
        }
        else
        {
            QMessageBox::critical(this, "Load Graph failed", "Unable to load a vertex-pair-weight graph");
        }
    }
}

void MainWindow::on_actionMovielens_format_triggered()
{
    // Load Movielens Format
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Movielens Graph"),
                   ".",
                   tr("All Files (*)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->loadGraphTypeMovieLens(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Graph Success", "Successfully loaded a Movielens type graph.");
            ui->nodePlotter->initGraph();
        }
        else
        {
            QMessageBox::critical(this, "Load Graph failed", "Unable to load a Movielens graph");
        }
    }
}

void MainWindow::on_actionSave_Population_triggered()
{
    // Save population
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Population"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->savePopulation(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Population Success", "Successfully saved population to file.");
        }
        else
        {
            QMessageBox::critical(this, "Save Population failed", "Unable to save population");
        }
    }
}

void MainWindow::on_actionLoad_Population_triggered()
{
    // Load population
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Load Population"),
                   ".",
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        bool result = clb::GlobalBackendController::instance()->loadPopulation(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Population Success", "Successfully loaded a population.");
        }
        else
        {
            QMessageBox::critical(this, "Load Population failed", "Unable to load a population out of this file.");
        }
    }
}


void MainWindow::on_actionAbout_2_triggered()
{
    QString info = "Clustering Social Networks by using Genetic Algorithms\n\n"
                   "Software Project for the Course Software Engineering Lab 2015 at Jacobs University Bremen.\n\n"
                   "Authors: Denis Rochau, Dinesh Kannan, Annu Thapa, Valentin Vasiliu, Radu Homorozan, Kiril Kafadarov";
    QMessageBox::about(this, "About this project", info);
}

void MainWindow::on_actionEdit_Settings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

}
}
