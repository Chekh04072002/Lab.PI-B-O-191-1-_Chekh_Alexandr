#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <map>
#include <sstream>

using namespace sf;
using namespace std;

string HOST = "127.0.0.1";
int PORT = 30780;

int WIDTH = 800;
int HEIGHT = 500;

int padSize = 30;
int ballSize = 5;

string int_to_string(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

void centerTextAt(Text* text, float x, float y) {
    FloatRect textRect = text->getLocalBounds();
    text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text->setPosition(Vector2f(x, y));
}

void centerShapeAt(Shape* shape, float x, float y) {
    FloatRect rect = shape->getLocalBounds();
    shape->setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    shape->setPosition(Vector2f(x, y));
}

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Aerohockey");

    Font font;
    font.loadFromFile("fff.ttf");

    Text infoText;
    infoText.setFont(font);
    infoText.setString("Failed to connect to server");
    infoText.setFillColor(Color::White);

    int score1 = 0;
    int score2 = 0;

    Text score1Text;
    score1Text.setFont(font);
    score1Text.setString("0");
    score1Text.setFillColor(Color::White);
    centerTextAt(&score1Text, 50, 50);

    Text score2Text;
    score2Text.setFont(font);
    score2Text.setString("0");
    score2Text.setFillColor(Color::White);
    centerTextAt(&score2Text, WIDTH - 50, 50);

    centerTextAt(&infoText, WIDTH / 2, HEIGHT / 2);

    bool failedToConnect = false;
    bool gameInProgress = false;

    TcpSocket serverSocket;

    if (serverSocket.connect(HOST, PORT) != Socket::Done) {
        failedToConnect = true;
    } else {
        infoText.setString("Waiting for player2");
        centerTextAt(&infoText, WIDTH / 2, HEIGHT / 2);
    }

    serverSocket.setBlocking(false);

    CircleShape pad1;
    pad1.setRadius(padSize);
    pad1.setFillColor(Color::White);
    centerShapeAt(&pad1, 100, HEIGHT / 2);

    CircleShape pad2;
    pad2.setRadius(padSize);
    pad2.setFillColor(Color::White);
    centerShapeAt(&pad2, WIDTH - 100, HEIGHT / 2);

    CircleShape ball;
    ball.setRadius(ballSize);
    ball.setFillColor(Color::White);
    centerShapeAt(&ball, WIDTH / 2, HEIGHT / 2);

    RectangleShape wallTop;
    wallTop.setSize(Vector2f(WIDTH, 10));
    wallTop.setOutlineColor(Color::White);
    wallTop.setPosition(0, 0);

    RectangleShape wallBot;
    wallBot.setSize(Vector2f(WIDTH, 10));
    wallBot.setOutlineColor(Color::White);
    wallBot.setPosition(0, HEIGHT - 10);

    RectangleShape wallLeft1;
    wallLeft1.setSize(Vector2f(10, 0.35 * HEIGHT));
    wallLeft1.setOutlineColor(Color::White);
    wallLeft1.setPosition(0, 0);

    RectangleShape wallLeft2;
    wallLeft2.setSize(Vector2f(10, 0.35 * HEIGHT));
    wallLeft2.setOutlineColor(Color::White);
    wallLeft2.setPosition(0, 0.65 * HEIGHT);

    RectangleShape wallRight1;
    wallRight1.setSize(Vector2f(10, 0.35 * HEIGHT));
    wallRight1.setOutlineColor(Color::White);
    wallRight1.setPosition(WIDTH - 10, 0);

    RectangleShape wallRight2;
    wallRight2.setSize(Vector2f(10, 0.35 * HEIGHT));
    wallRight2.setOutlineColor(Color::White);
    wallRight2.setPosition(WIDTH - 10, 0.65 * HEIGHT);

    bool pressedW = false;
    bool pressedS = false;
    bool pressedD = false;
    bool pressedA = false;

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (gameInProgress && event.key.code == Keyboard::W && !pressedW) {
                    pressedW = true;
                    Packet packet;
                    packet << "Press" << "w";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::S && !pressedS) {
                    pressedS = true;
                    Packet packet;
                    packet << "Press" << "s";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::D && !pressedD) {
                    pressedD = true;
                    Packet packet;
                    packet << "Press" << "d";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::A && !pressedA) {
                    pressedA = true;
                    Packet packet;
                    packet << "Press" << "a";
                    serverSocket.send(packet);
                }
            }

            if (event.type == Event::KeyReleased) {
                if (gameInProgress && event.key.code == Keyboard::W) {
                    pressedW = false;
                    Packet packet;
                    packet << "Release" << "w";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::S) {
                    pressedS = false;
                    Packet packet;
                    packet << "Release" << "s";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::D) {
                    pressedD = false;
                    Packet packet;
                    packet << "Release" << "d";
                    serverSocket.send(packet);
                }
                if (gameInProgress && event.key.code == Keyboard::A) {
                    pressedA = false;
                    Packet packet;
                    packet << "Release" << "a";
                    serverSocket.send(packet);
                }
            }
        }

        Packet packet;
        string type;

        Socket::Status status = serverSocket.receive(packet);

        if (status == Socket::Status::Disconnected && !failedToConnect) {
            gameInProgress = false;
            infoText.setString("Connection lost");
            centerTextAt(&infoText, WIDTH / 2, HEIGHT / 2);
        } else if (status == Socket::Status::Done) {
            packet >> type;

            if (type == "Server full") {
                failedToConnect = true;
                infoText.setString("Server full");
            } else if (type == "Game start") {
                gameInProgress = true;
            } else if (type == "Move pad1") {
                float x, y;

                packet >> x >> y;

                centerShapeAt(&pad1, x, y);
            } else if (type == "Move pad2") {
                float x, y;

                packet >> x >> y;

                centerShapeAt(&pad2, x, y);
            } else if (type == "Move ball") {
                float x, y;

                packet >> x >> y;

                centerShapeAt(&ball, x, y);
            } else if (type == "Score") {
                bool player1;

                packet >> player1;

                if (player1) {
                    score1++;
                    score1Text.setString(int_to_string(score1));
                    centerTextAt(&score1Text, 50, 50);
                } else {
                    score2++;
                    score2Text.setString(int_to_string(score2));
                    centerTextAt(&score2Text, WIDTH - 50, 50);
                }
            }

            centerTextAt(&infoText, WIDTH / 2, HEIGHT / 2);
        }

        window.clear();
        
        if (!gameInProgress) {
            window.draw(infoText);
        } else {
            window.draw(pad1);
            window.draw(pad2);
            window.draw(ball);
            window.draw(wallTop);
            window.draw(wallBot);
            window.draw(wallLeft1);
            window.draw(wallLeft2);
            window.draw(wallRight1);
            window.draw(wallRight2);
            window.draw(score1Text);
            window.draw(score2Text);
        }

        window.display();
    }

    return 0;
}