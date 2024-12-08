#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <unordered_map>
#include <QMessageBox>

class Portfolio {
private:
    std::unordered_map<std::string, double> positions; // Symbol -> Quantity
    std::unordered_map<std::string, double> prices;    // Symbol -> Price

public:
    // Method to add a position to the portfolio
    void addPosition(const std::string& symbol, double quantity, double price);

    // Method to get the total value of the portfolio
    double getPortfolioValue() const;

    // Getter for positions (symbol -> quantity)
    const std::unordered_map<std::string, double>& getPositions() const;

    // Getter for prices (symbol -> price)
    const std::unordered_map<std::string, double>& getPrices() const;
};

class MainWindow : public QMainWindow {
    Q_OBJECT  // Ensure the Q_OBJECT macro is here

private:
    Portfolio portfolio;         // Portfolio instance to hold positions and prices
    QTableWidget* portfolioTable; // Table to display portfolio data
    QLabel* portfolioValueLabel; // Label to display total portfolio value
    QLineEdit* symbolInput;      // Input field for symbol (e.g., AAPL)
    QLineEdit* quantityInput;    // Input field for quantity (e.g., 10)
    QLineEdit* priceInput;       // Input field for price (e.g., 150.0)

    // Method to update the UI with the current portfolio value and table
    void updateUI();

public:
    // Constructor to initialize the main window
    MainWindow(QWidget* parent = nullptr);

    // Destructor
    ~MainWindow();

private slots:
    // Slot to handle adding a position to the portfolio
    void onAddPosition();
};

#endif // MAINWINDOW_H
