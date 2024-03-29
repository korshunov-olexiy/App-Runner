#include <nlohmann/json.hpp>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMenu>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using json = nlohmann::json;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Читання JSON-файлу
    std::ifstream file("commands.json");
    json j;
    file >> j;

    // Створення іконки в системному треї
    QSystemTrayIcon trayIcon(QIcon("app.png"));
    trayIcon.setVisible(true);

    QMenu trayMenu;

    // Додавання пунктів меню на основі JSON-файлу
    for (auto& element : j.items()) {
        std::string command = element.value();
        QAction *action = trayMenu.addAction(element.key().c_str());

        QObject::connect(action, &QAction::triggered, [command](){
            system(command.c_str());
        });
    }

    // Додаємо пункт "Вихід з програми"
    QAction *exitAction = trayMenu.addAction("Вихід з програми");
    QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);

    // Закриття меню при втраті фокусу
    QObject::connect(&trayMenu, &QMenu::aboutToHide, [&](){
        // Код для обробки закриття меню (якщо потрібно)
    });

    trayIcon.setContextMenu(&trayMenu);

    return app.exec();
}
