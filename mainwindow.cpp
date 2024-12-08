#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <unordered_map>
#include <QMessageBox>
#include <QTableWidgetItem> // Ensure this is included for using QTableWidgetItem

class Portfolio {
private:
    std::unordered_map<std::string, double> positions; // Symbol -> Quantity
    std::unordered_map<std::string, double> prices;    // Symbol -> Price

public:
    // Add a position to the portfolio
    void addPosition(const std::string& symbol, double quantity, double price) {
        positions[symbol] += quantity;
        prices[symbol] = price;
    }

    // Get the total portfolio value
    double getPortfolioValue() const {
        double totalValue = 0.0;
        for (const auto& [symbol, quantity] : positions) {
            totalValue += quantity * prices.at(symbol);
        }
        return totalValue;
    }

    // Get all positions (symbol -> quantity)
    const std::unordered_map<std::string, double>& getPositions() const {
        return positions;
    }

    // Get all prices (symbol -> price)
    const std::unordered_map<std::string, double>& getPrices() const {
        return prices;
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT  // Necessary for Qt's meta-object system

private:
    Portfolio portfolio;
    QTableWidget* portfolioTable;
    QLabel* portfolioValueLabel;
    QLineEdit* symbolInput;
    QLineEdit* quantityInput;
    QLineEdit* priceInput;

    // Update the UI with the latest portfolio value and table data
    void updateUI() {
        // Update portfolio value label
        double portfolioValue = portfolio.getPortfolioValue();
        portfolioValueLabel->setText("Portfolio Value: $" + QString::number(portfolioValue, 'f', 2));

        // Update the table with positions
        int row = 0;
        for (const auto& [symbol, quantity] : portfolio.getPositions()) {
            bool symbolFound = false;
            // Check if the symbol already exists in the table
            for (int r = 0; r < portfolioTable->rowCount(); r++) {
                if (portfolioTable->item(r, 0)->text() == QString::fromStdString(symbol)) {
                    symbolFound = true;
                    // Update the existing row
                    portfolioTable->item(r, 1)->setText(QString::number(quantity));
                    portfolioTable->item(r, 2)->setText(QString::number(portfolio.getPrices().at(symbol), 'f', 2));
                    break;
                }
            }
            // If the symbol is not found, add a new row
            if (!symbolFound) {
                portfolioTable->insertRow(row);
                portfolioTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(symbol)));
                portfolioTable->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
                portfolioTable->setItem(row, 2, new QTableWidgetItem(QString::number(portfolio.getPrices().at(symbol), 'f', 2)));
                row++;
            }
        }
    }

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Risk Management System");

        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        // Portfolio value label
        portfolioValueLabel = new QLabel("Portfolio Value: $0.00", this);
        layout->addWidget(portfolioValueLabel);

        // Portfolio table to display positions (Symbol, Quantity, Price)
        portfolioTable = new QTableWidget(this);
        portfolioTable->setColumnCount(3);
        portfolioTable->setHorizontalHeaderLabels({"Symbol", "Quantity", "Price"});
        layout->addWidget(portfolioTable);

        // Input fields for adding a new position
        symbolInput = new QLineEdit(this);
        symbolInput->setPlaceholderText("Enter symbol (e.g., AAPL)");
        layout->addWidget(symbolInput);

        quantityInput = new QLineEdit(this);
        quantityInput->setPlaceholderText("Enter quantity (e.g., 10)");
        layout->addWidget(quantityInput);

        priceInput = new QLineEdit(this);
        priceInput->setPlaceholderText("Enter price (e.g., 150.0)");
        layout->addWidget(priceInput);

        // Button to add a new position to the portfolio
        QPushButton* addButton = new QPushButton("Add Position", this);
        layout->addWidget(addButton);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddPosition);

        setCentralWidget(centralWidget);
        resize(600, 400);
    }

    ~MainWindow() {}

private slots:
    // Slot to handle adding a new position
    void onAddPosition() {
        std::string symbol = symbolInput->text().toStdString();
        bool okQuantity, okPrice;
        double quantity = quantityInput->text().toDouble(&okQuantity);
        double price = priceInput->text().toDouble(&okPrice);

        // Validate input
        if (symbol.empty() || !okQuantity || !okPrice || quantity <= 0 || price <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter valid symbol, quantity, and price.");
            return;
        }

        // Add the position to the portfolio
        portfolio.addPosition(symbol, quantity, price);

        // Update the UI
        updateUI();

        // Clear input fields
        symbolInput->clear();
        quantityInput->clear();
        priceInput->clear();
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
