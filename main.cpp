#include "StockManager.h"
#include "OrderManager.h"
#include "ConcreteStockItem.h"
#include "Worker.h"
#include "Tool.h"
#include "Machine.h"
#include <iostream>
#include <string>
#include "Inputs.h"
#include "gtest_lite.h"
#include "memtrace.h"
/*
 * Az input és output áramok átirányítását végző függvény definíciója.
 * */
void redirectStreams(std::stringstream& input, std::stringstream& output) {
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());
}
/*
 * Főmenüt megjelenítő függvény
 * */
void displayMenu() {
    std::cout<<"\n"
               "  /$$$$$$                                  /$$                                     /$$    \n"
               " /$$__  $$                                | $$                                    | $$    \n"
               "| $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$  /$$   /$$  /$$$$$$$ /$$$$$$  \n"
               "| $$       /$$__  $$| $$__  $$ /$$_____/|_  $$_/   /$$__  $$| $$  | $$ /$$_____/|_  $$_/  \n"
               "| $$      | $$  \\ $$| $$  \\ $$|  $$$$$$   | $$    | $$  \\__/| $$  | $$| $$        | $$    \n"
               "| $$    $$| $$  | $$| $$  | $$ \\____  $$  | $$ /$$| $$      | $$  | $$| $$        | $$ /$$\n"
               "|  $$$$$$/|  $$$$$$/| $$  | $$ /$$$$$$$/  |  $$$$/| $$      |  $$$$$$/|  $$$$$$$  |  $$$$/\n"
               " \\______/  \\______/ |__/  |__/|_______/    \\___/  |__/       \\______/  \\_______/   \\___/  \n"
               "                                                                                          \n"
               "                                                                                          \n"
               "                                                                                          ";
    std::cout << "\n";
    std::cout << "1. Add Stock Item\n";
    std::cout << "2. Create Order\n";
    std::cout << "3. Display All Stock Items\n";
    std::cout << "4. Display All Orders\n";
    std::cout << "5. Remove Item From Stock\n";
    std::cout << "6. Delete An Order\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
    std::cout << "\n";
}
/* main függvény */
int main() {
#ifndef CPORTA
    StockManager stockManager;
    OrderManager orderManager;
    std::string filename_stock = R"(stocks.csv)";
    std::string filename_order = R"(orders.csv)";
    stockManager.readStocksFromFile(filename_stock);
    orderManager.readOrdersFromFile(filename_order,stockManager);
    while (true) {
        displayMenu();
        int choice = readNumber<int>("");
        switch (choice) {
            case 1:
                StockManager::addItem(stockManager);
                stockManager.updateStocksInFile(filename_stock);
                break;
            case 2:
                orderManager.createOrder(stockManager);
                orderManager.writeOrdersToFile(filename_order);
                stockManager.updateStocksInFile(filename_stock);
                break;
            case 3:
                stockManager.displayAllStocks();
                break;
            case 4:
                orderManager.displayAllOrders();
                break;
            case 5:
                stockManager.removeStockItemById();
                stockManager.updateStocksInFile(filename_stock);
                break;
            case 6:
                orderManager.deleteOrder();
                orderManager.updateOrdersInFile(filename_order);
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
#else
    //tesztek
    std::stringstream input, output;
    TEST(VectorTest, DefaultConstructor)
        {
            Vector<int> v;
            ASSERT_EQ(0, v.size());
        }END
    TEST(VectorTest, PushBack)
        {
            Vector<int> v;
            v.push_back(5);
            v.push_back(10);
            ASSERT_EQ(2, v.size());
            ASSERT_EQ(5, v[0]);
            ASSERT_EQ(10, v[1]);
        }END
    TEST(VectorTest, PopBack)
        {
            Vector<int> v;
            v.push_back(5);
            v.push_back(10);
            v.pop_back();
            ASSERT_EQ(1, v.size());
            ASSERT_EQ(5, v[0]);
        }END
    TEST(VectorTest, At)
        {
            Vector<int> v;
            v.push_back(5);
            v.push_back(10);
            ASSERT_EQ(5, v.at(0));
            ASSERT_EQ(10, v.at(1));
        }END
    TEST(VectorTest, Erase)
        {
            Vector<int> v;
            v.push_back(5);
            v.push_back(10);
            v.erase(0);
            ASSERT_EQ(1, v.size());
            ASSERT_EQ(10, v[0]);
        }END
    TEST(ConcreteStockItem, ConstructorAndGetters) {
            ConcreteStockItem s(1, "Item1", 10.0, 5);
            ASSERT_EQ(1, s.getId());
            ASSERT_EQ(std::string{"Item1"}, s.getName());
            ASSERT_EQ(10.0, s.getPrice());
            ASSERT_EQ(5, s.getCount());
        }END
    TEST(ConcreteStockItem, UpdateCount) {
            ConcreteStockItem s(1, "Item1", 10.0, 5);
            s.updateCount(3);
            ASSERT_EQ(8, s.getCount());
            s.updateCount(-2);
            ASSERT_EQ(6, s.getCount());
        }ENDM
    TEST(Worker, ConstructorAndGetters) {
            Worker w(1, "John", 100.0, 5, "Engineer");
            ASSERT_EQ(1, w.getId());
            ASSERT_EQ(std::string{"John"}, w.getName());
            ASSERT_EQ(100.0, w.getPrice());
            ASSERT_EQ(5, w.getCount());
            ASSERT_EQ(std::string{"Engineer"}, w.getSpecialization());
        }END
    TEST(Worker, DisplayInStock) {
            Worker w(1, "John", 100.0, 5, "Engineer");
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                w.display();
            }
            ASSERT_EQ(std::string{"Worker [ID=1, Name=John, Price=100, Count=5, Spec=Engineer]\n"}, ss.str());
        }ENDM
    TEST(Worker, DisplayOutOfStock) {
            Worker w(1, "John", 100.0, 0, "Engineer");
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                w.display();
            }
            ASSERT_EQ(std::string{"Item with ID = 1 is out of stock\n"}, ss.str());
        }END
    TEST(Tool, ConstructorAndGetters) {
            Tool t(1, "Hammer", 10.0, 5, 2.5);
            ASSERT_EQ(1, t.getId());
            ASSERT_EQ(std::string{"Hammer"}, t.getName());
            ASSERT_EQ(5, t.getCount());
            ASSERT_EQ(2.5, t.getHeavinessIndex());
        }END
    TEST(Tool, DisplayInStock) {
            Tool t(1, "Hammer", 10.0, 5, 2.5);
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                t.display();
            }
            ASSERT_EQ(std::string{"Tool [ID=1, Name=Hammer, Price=10, Count=5, Heaviness Index=2.5]\n"}, ss.str());
        }END

    TEST(Tool, DisplayOutOfStock) {
            Tool t(1, "Hammer", 10.0, 0, 2.5);
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                t.display();
            }
            ASSERT_EQ(std::string{"Item with ID = 1 is out of stock\n"}, ss.str());
        }END
    TEST(Machine, ConstructorAndGetters) {
            Machine m(1, "Machine1", 100.0, 5, 1);
            ASSERT_EQ(1, m.getId());
            ASSERT_EQ(std::string{"Machine1"}, m.getName());
            ASSERT_EQ(100.0, m.getPrice());
            ASSERT_EQ(5, m.getCount());
            EXPECT_TRUE(m.NeedsConductor());
        }END

    TEST(Machine, DisplayInStock) {
            Machine m(1, "Machine1", 100.0, 5, true);
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                m.display();
            }
            ASSERT_EQ(std::string{"Machine [ID=1, Name=Machine1, Price=100, Count=5, Needs Conductor=Yes]\n"}, ss.str())
        }END

    TEST(Machine, DisplayOutOfStock) {
            Machine m(1, "Machine1", 100.0, 0, true);
            std::stringstream ss;
            {
                gtest_lite::ostreamRedir redirect(std::cout, ss);
                m.display();
            }
            ASSERT_EQ(std::string{"Item with ID = 1 is out of stock\n"}, ss.str())
        }END

    TEST(PairTest, DefaultConstructor) {
            Pair<int, double> p{};
            EXPECT_EQ(p.first, 0);
            EXPECT_EQ(p.second, 0.0);
        } END
    TEST(PairTest, ParameterizedConstructor) {
            Pair<int, double> p(42, 3.14);
            EXPECT_EQ(p.first, 42);
            EXPECT_EQ(p.second, 3.14);
        } END
    TEST(PairTest, MakePairFunction) {
            auto p = make_pair(42, 3.14);
            EXPECT_EQ(p.first, 42);
            EXPECT_EQ(p.second, 3.14);
        } END
    TEST(PairTest, DifferentTypes) {
            Pair<std::string, char> p("hello", 'a');
            EXPECT_EQ(p.first, "hello");
            EXPECT_EQ(p.second, 'a');
        } END
    TEST(PairTest, ModifyValues) {
            Pair<int, double> p(42, 3.14);
            p.first = 10;
            p.second = 2.71;
            EXPECT_EQ(p.first, 10);
            EXPECT_EQ(p.second, 2.71);
        } END
    TEST(StockManager, AddStockItem) {
            StockManager stockManager;
            auto* worker = new Worker(1, "John", 1000.0, 1, "Engineer");
            stockManager.addStockItem(worker);
            EXPECT_EQ(1, stockManager.getStockById(1)->getId());
            EXPECT_EQ(std::string{"John"}, stockManager.getStockById(1)->getName());
            EXPECT_EQ(1000.0, stockManager.getStockById(1)->getPrice());
            EXPECT_EQ(1, stockManager.getStockById(1)->getCount());
            EXPECT_EQ(std::string{"Engineer"}, dynamic_cast<Worker*>(stockManager.getStockById(1))->getSpecialization());
        } END
    TEST(StockManager, HasSameIdInCategory) {
            StockManager stockManager;
            auto* worker2 = new Worker(2, "Jane", 1200.0, 1, "Architect");
            stockManager.addStockItem(worker2);
            EXPECT_TRUE(stockManager.hasSameIdInCategory(2, "Worker"));
            EXPECT_FALSE(stockManager.hasSameIdInCategory(3, "Worker"));
        } END
    TEST(StockManager, DecreaseStockItemCountById) {
            StockManager stockManager;
            auto* worker2 = new Worker(1, "Jane", 1200.0, 1, "Architect");
            stockManager.addStockItem(worker2);
            stockManager.decreaseStockItemCountById(1);
            EXPECT_EQ(0, stockManager.getStockById(1)->getCount());
        } END
    TEST(StockManagerTest, HasSameIdInCategory) {
            StockManager manager;
            manager.addStockItem(new Worker(1, "Worker1", 100.0, 1, "Specialization1"));
            manager.addStockItem(new Machine(2, "Machine1", 200.0, 1, true));
            manager.addStockItem(new Tool(3, "Tool1", 50.0, 1, 1.5));
            EXPECT_TRUE(manager.hasSameIdInCategory(1, "Worker"));
            EXPECT_FALSE(manager.hasSameIdInCategory(1, "Machine"));
            EXPECT_TRUE(manager.hasSameIdInCategory(2, "Machine"));
            EXPECT_FALSE(manager.hasSameIdInCategory(3, "Worker"));
        } END
    TEST(StockManagerTest, GetStockById) {
            StockManager manager;
            auto* worker = new Worker(1, "Worker1", 100.0, 1, "Specialization1");
            manager.addStockItem(worker);
            StockItem* item = manager.getStockById(1);
            EXPECT_EQ(item->getId(), 1);
            EXPECT_EQ(item->getName(), "Worker1");
        } END
    TEST(StockManagerTest, ReadStocksFromFile) {
            StockManager manager;
            std::ofstream file("test_stocks.csv");
            file << "Worker,1,Worker1,100.0,1,Specialization1\n";
            file << "Machine,2,Machine1,200.0,1,1\n";
            file << "Tool,3,Tool1,50.0,1,1.5\n";
            file.close();
            manager.readStocksFromFile("test_stocks.csv");
            EXPECT_TRUE(manager.hasSameIdInCategory(1, "Worker"));
            EXPECT_TRUE(manager.hasSameIdInCategory(2, "Machine"));
            EXPECT_TRUE(manager.hasSameIdInCategory(3, "Tool"));
            remove("test_stocks.csv");
        } END
    TEST(StockManagerTest, DecreaseStockItemCountById) {
            StockManager manager;
            auto* worker = new Worker(1, "Worker1", 100.0, 5, "Specialization1");
            manager.addStockItem(worker);
            manager.decreaseStockItemCountById(1);
            EXPECT_EQ(worker->getCount(), 4);
        } END
    TEST(StockManagerTest, DisplayAllStocks) {
            StockManager manager;
            manager.addStockItem(new Worker(1, "Worker1", 100.0, 1, "Specialization1"));
            manager.addStockItem(new Machine(2, "Machine1", 200.0, 1, true));
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());
            manager.displayAllStocks();
            std::cout.rdbuf(oldCoutBuffer);
            std::string expectedOutput =
                    "Worker [ID=1, Name=Worker1, Price=100, Count=1, Spec=Specialization1]\nMachine [ID=2, Name=Machine1, Price=200, Count=1, Needs Conductor=Yes]\n";
            EXPECT_EQ(output.str(), expectedOutput);
        } END
    TEST(StockManagerTest, WriteAndUpdateStocksToFile) {
            StockManager manager;
            manager.addStockItem(new Worker(1, "Worker1", 100.0, 1, "Specialization1"));
            manager.addStockItem(new Machine(2, "Machine1", 200.0, 1, true));
            manager.writeStocksToFile("output_stocks.csv");
            std::ifstream file("output_stocks.csv");
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            std::string expectedOutput =
                    "Worker,1,Worker1,100,1,Specialization1\n"
                    "Machine,2,Machine1,200,1,1\n";
            EXPECT_EQ(buffer.str(), expectedOutput);
            manager.updateStocksInFile("output_stocks.csv");
            std::ifstream fileUpdated("output_stocks.csv");
            std::stringstream bufferUpdated;
            bufferUpdated << fileUpdated.rdbuf();
            fileUpdated.close();
            EXPECT_EQ(bufferUpdated.str(), expectedOutput);
            remove("output_stocks.csv");
        } END
    TEST(OrderTest, ConstructorAndGetters) {
            Order order(1, "John Doe");
            EXPECT_EQ(order.getId(), 1);
            EXPECT_EQ(order.getCustomerName(), "John Doe");
        }END
    TEST(OrderTest, GetId) {
            Order order(1, "John Doe");
            EXPECT_EQ(order.getId(), 1);
        }END
    TEST(OrderTest, GetCustomerName) {
            Order order(1, "John Doe");
            EXPECT_EQ(order.getCustomerName(), "John Doe");
        }END
    TEST(OrderTest, AddItem) {
            Order order(1, "John Doe");
            StockItem* item = new ConcreteStockItem(1, "Hammer", 10.0, 5);
            order.addItem(item, 2);
            EXPECT_EQ(order.getItems().size(), 1);
            EXPECT_EQ(item->getCount(), 3);
            delete item;
        }END
    TEST(OrderTest, GetItems) {
            Order order(1, "John Doe");
            StockItem* item1 = new ConcreteStockItem(1, "Hammer", 10.0, 5);
            StockItem* item2 = new ConcreteStockItem(2, "Nail", 0.1, 100);
            order.addItem(item1, 2);
            order.addItem(item2, 50);
            const auto& items = order.getItems();
            EXPECT_EQ(items.size(), 2);
            EXPECT_EQ(items[0].first->getId(), 1);
            EXPECT_EQ(items[0].second, 2);
            EXPECT_EQ(items[0].first->getName(), "Hammer");
            EXPECT_EQ(items[0].first->getCount(), 3);
            EXPECT_EQ(items[1].first->getId(), 2);
            EXPECT_EQ(items[1].second, 50);
            EXPECT_EQ(items[1].first->getName(), "Nail");
            EXPECT_EQ(items[1].first->getCount(), 50);
            delete item1;
            delete item2;
        } END
    TEST(OrderTest, Display) {
            Order order(1, "John Doe");
            StockItem* item1 = new ConcreteStockItem(1, "Hammer", 10.0, 5);
            StockItem* item2 = new ConcreteStockItem(2, "Nail", 0.1, 100);
            order.addItem(item1, 2);
            order.addItem(item2, 50);
            std::stringstream ss;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(ss.rdbuf());
            order.display();
            std::cout.rdbuf(oldCoutBuffer);
            std::string expectedOutput =
                    "Order [ID=1, Customer=John Doe]\n"
                    "  Item [ID=1, Name=Hammer, Price=10, Quantity=2]\n"
                    "  Item [ID=2, Name=Nail, Price=0.1, Quantity=50]\n";
            EXPECT_EQ(ss.str(), expectedOutput);
            delete item1;
            delete item2;
        } END
    TEST(OrderTest, DisplayOffer) {
            Order order(1, "John Doe");
            StockItem* item1 = new ConcreteStockItem(1, "Hammer", 10.0, 5);
            StockItem* item2 = new ConcreteStockItem(2, "Nail", 0.1, 100);
            order.addItem(item1, 2);
            order.addItem(item2, 50);
            std::stringstream ss;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(ss.rdbuf());
            order.displayOffer();
            std::cout.rdbuf(oldCoutBuffer);
            std::string expectedOutput =
                    "Order offer [ID=1, Customer=John Doe]\n"
                    "  Item [ID=1, Name=Hammer, Price=10, Quantity=2, Total Price=20]\n"
                    "  Item [ID=2, Name=Nail, Price=0.1, Quantity=50, Total Price=5]\n"
                    "Total Order Price: 25\n";
            EXPECT_EQ(ss.str(), expectedOutput);
            delete item1;
            delete item2;
        } END
    TEST(StockManagerTest, AddItem) {
            StockManager stockManager;
            std::stringstream input;
            input << "Worker\n" // Típus
                  << "1\n" // ID
                  << "John Doe\n" // Név
                  << "1000.0\n" // Ár
                  << "10\n" // Darabszám
                  << "Engineer\n"; // Specializáció
            std::cin.rdbuf(input.rdbuf());
            StockManager::addItem(stockManager);
            const StockItem* item = stockManager.getStockById(1);
            EXPECT_EQ(item->getId(), 1);
            EXPECT_EQ(item->getName(), "John Doe");
            EXPECT_EQ(item->getPrice(), 1000.0);
            EXPECT_EQ(item->getCount(), 10);
            EXPECT_EQ(dynamic_cast<const Worker*>(item)->getSpecialization(), "Engineer");
            input.clear();
            input.str("");
            input << "Machine\n" // Típus
                  << "2\n" // ID
                  << "Excavator\n" // Név
                  << "50000.0\n" // Ár
                  << "5\n" // Darabszám
                  << "1\n"; // Kell-e vezető
            std::cin.rdbuf(input.rdbuf());
            StockManager::addItem(stockManager);
            item = stockManager.getStockById(2);
            EXPECT_EQ(item->getId(), 2);
            EXPECT_EQ(item->getName(), "Excavator");
            EXPECT_EQ(item->getPrice(), 50000.0);
            EXPECT_EQ(item->getCount(), 5);
            EXPECT_TRUE(dynamic_cast<const Machine*>(item)->NeedsConductor());
            input.clear();
            input.str("");
            input << "Tool\n" // Típus
                  << "3\n" // ID
                  << "Hammer\n" // Név
                  << "50.0\n" // Ár
                  << "20\n" // Darabszám
                  << "1.5\n"; // Súlyossági index
            std::cin.rdbuf(input.rdbuf());
            StockManager::addItem(stockManager);
            item = stockManager.getStockById(3);
            EXPECT_EQ(item->getId(), 3);
            EXPECT_EQ(item->getName(), "Hammer");
            EXPECT_EQ(item->getPrice(), 50.0);
            EXPECT_EQ(item->getCount(), 20);
            EXPECT_EQ(dynamic_cast<const Tool*>(item)->getHeavinessIndex(), 1.5);
            std::cin.rdbuf(nullptr);
        } END
    TEST(VectorTest, ConstOperatorBracket) {
            // Create a vector and populate it with some values
            Vector<int> v;
            v.push_back(10);
            v.push_back(20);
            v.push_back(30);

            // Test accessing elements using the const version of operator[]
            const Vector<int>& constV = v;
            EXPECT_EQ(constV[0], 10); // Accessing the first element
            EXPECT_EQ(constV[1], 20); // Accessing the second element
            EXPECT_EQ(constV[2], 30); // Accessing the third element
        } END
    TEST(StockManagerTest, GetStocks) {
            // Create a StockManager instance
            StockManager stockManager;

            // Add some stock items to the StockManager
            stockManager.addStockItem(new ConcreteStockItem(1, "Item1", 10.0, 5));
            stockManager.addStockItem(new ConcreteStockItem(2, "Item2", 20.0, 3));

            // Retrieve the vector of stock items using getStocks method
            const Vector<StockItem*>& stocks = stockManager.getStocks();

            // Verify that the size of the returned vector matches the number of added items
            EXPECT_EQ(stocks.size(), 2);

            // Verify the content of the returned vector
            EXPECT_EQ(stocks[0]->getId(), 1);
            EXPECT_EQ(stocks[0]->getName(), "Item1");
            EXPECT_EQ(stocks[0]->getPrice(), 10.0);
            EXPECT_EQ(stocks[0]->getCount(), 5);

            EXPECT_EQ(stocks[1]->getId(), 2);
            EXPECT_EQ(stocks[1]->getName(), "Item2");
            EXPECT_EQ(stocks[1]->getPrice(), 20.0);
            EXPECT_EQ(stocks[1]->getCount(), 3);
        } END
    TEST(OrderManagerTest, AddOrderAndOrderExists) {
            OrderManager orderManager;
            Order* order1 = new Order(1, "Customer1");
            Order* order2 = new Order(2, "Customer2");
            orderManager.addOrder(order1);
            orderManager.addOrder(order2);
            EXPECT_TRUE(orderManager.orderExists(1));
            EXPECT_TRUE(orderManager.orderExists(2));
            EXPECT_FALSE(orderManager.orderExists(3));
        } END
    TEST(ConcreteStockItemTest, Display)    {
    ConcreteStockItem item(1, "TestItem", 99.99, 10);
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    item.display();
    std::cout.rdbuf(oldCout);
    std::string expectedOutput = "StockItem [ID=1, Name=TestItem, Price=99.99, Count=10]\n";
    EXPECT_EQ(buffer.str(), expectedOutput);
}END


#endif
}
