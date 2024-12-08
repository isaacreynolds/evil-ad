#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <unordered_map>
#include <QString>
#include <QObject>

class Portfolio {
private:
    std::unordered_map<std::string, double> positions; // Symbol -> Quantity
    std::unordered_map<std::string, double> prices;    // Symbol -> Price

public:
    void addPosition(const std::string& symbol, double quantity, double price);
    double getPortfolioValue() const;
    const std::unordered_map<std::string, double>& getPositions() const;
    const std::unordered_map<std::string, double>& getPrices() const;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Portfolio portfolio;
    QTableWidget* portfolioTable;
    QLabel* portfolioValueLabel;
    QLineEdit* symbolInput;
    QLineEdit* quantityInput;
    QLineEdit* priceInput;

    void updateUI();

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddPosition();
};

#endif // MAINWINDOW_H
