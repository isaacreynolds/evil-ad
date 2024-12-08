#include "mainwindow.h"
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QString>

// Constructor definition
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Risk Management System");

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    portfolioValueLabel = new QLabel("Portfolio Value: $0.00", this);
    layout->addWidget(portfolioValueLabel);

    portfolioTable = new QTableWidget(this);
    portfolioTable->setColumnCount(3);
    portfolioTable->setHorizontalHeaderLabels({"Symbol", "Quantity", "Price"});
    layout->addWidget(portfolioTable);

    symbolInput = new QLineEdit(this);
    symbolInput->setPlaceholderText("Enter symbol (e.g., AAPL)");
    layout->addWidget(symbolInput);

    quantityInput = new QLineEdit(this);
    quantityInput->setPlaceholderText("Enter quantity (e.g., 10)");
    layout->addWidget(quantityInput);

    priceInput = new QLineEdit(this);
    priceInput->setPlaceholderText("Enter price (e.g., 150.0)");
    layout->addWidget(priceInput);

    QPushButton* addButton = new QPushButton("Add Position", this);
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddPosition);

    setCentralWidget(centralWidget);
    resize(600, 400);
}

// Destructor definition
MainWindow::~MainWindow() {
    // Cleanup if necessary
}

// Slot function definition
void MainWindow::onAddPosition() {
    std::string symbol = symbolInput->text().toStdString();
    double quantity = quantityInput->text().toDouble();
    double price = priceInput->text().toDouble();

    if (!symbol.empty() && quantity > 0 && price > 0) {
        portfolio.addPosition(symbol, quantity, price);
        updateUI();

        // Clear inputs
        symbolInput->clear();
        quantityInput->clear();
        priceInput->clear();
    }
}

// Update UI to reflect current portfolio state
void MainWindow::updateUI() {
    double portfolioValue = portfolio.getPortfolioValue();
    portfolioValueLabel->setText("Portfolio Value: $" + QString::number(portfolioValue));

    portfolioTable->setRowCount(0);
    int row = 0;
    for (const auto& [symbol, quantity] : portfolio.getPositions()) {
        portfolioTable->insertRow(row);
        portfolioTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(symbol)));
        portfolioTable->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
        portfolioTable->setItem(row, 2, new QTableWidgetItem(QString::number(portfolio.getPrices().at(symbol))));
        row++;
    }
}
