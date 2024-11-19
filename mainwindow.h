#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <unordered_map>
#include <vector>
#include <string>
#include<iostream>


#include "Trie.h"
#include "BloomFilter.h"
using namespace std;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Trie* trie;
    BloomFilter* bloomFilter;
    QLineEdit* inputLineEdit;
    QListWidget* suggestionListWidget;
    QPushButton* searchButton;

    // Categorized words for each alphabet
    unordered_map<char, vector<string>> alphabetWords;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchButtonClicked();
    void onTextChanged(const QString& text);

private:
    void setupUI();
    void populateBloomFilterAndTrie();
    void configureStyles();
   vector<string> findSimilarWords(const string& word);
};

#endif // MAINWINDOW_H
