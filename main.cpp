#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

int main()
{
    const unsigned int WIDTH = 900;
    const unsigned int HEIGHT = 600;
    const int WINNING_SCORE = 5;

    RenderWindow window(VideoMode(Vector2u(WIDTH, HEIGHT)), "Pong Oyunu");
    window.setFramerateLimit(60);

    RectangleShape leftPaddle(Vector2f(20.f, 120.f));
    leftPaddle.setPosition(Vector2f(40.f, 240.f));
    leftPaddle.setFillColor(Color::Cyan);

    RectangleShape rightPaddle(Vector2f(20.f, 120.f));
    rightPaddle.setPosition(Vector2f(840.f, 240.f));
    rightPaddle.setFillColor(Color::Red);

    CircleShape ball(12.f);
    ball.setPosition(Vector2f(444.f, 294.f));
    ball.setFillColor(Color::White);

    float paddleSpeed = 7.f;
    float aiSpeed = 4.f;
    float ballSpeedX = 5.f;
    float ballSpeedY = 4.f;

    int leftScore = 0;
    int rightScore = 0;

    bool menuScreen = true;
    bool singlePlayer = false;
    bool gameOver = false;
    bool paused = false;

    Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "arial.ttf bulunamadi." << std::endl;
        return 0;
    }

    Text titleText(font, "PONG OYUNU", 60);
    titleText.setFillColor(Color::White);
    titleText.setPosition(Vector2f(250.f, 110.f));

    Text onePlayerText(font, "Tek Oyuncu", 42);
    onePlayerText.setFillColor(Color::Yellow);
    onePlayerText.setPosition(Vector2f(330.f, 260.f));

    Text twoPlayerText(font, "Cift Oyuncu", 42);
    twoPlayerText.setFillColor(Color::Yellow);
    twoPlayerText.setPosition(Vector2f(330.f, 340.f));

    Text scoreText(font, "", 40);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(370.f, 20.f));

    Text infoText(font, "P: Pause   R: Restart   ESC: Menu", 20);
    infoText.setFillColor(Color::White);
    infoText.setPosition(Vector2f(260.f, 560.f));

    Text modeText(font, "", 22);
    modeText.setFillColor(Color::White);
    modeText.setPosition(Vector2f(20.f, 20.f));

    Text winnerText(font, "", 45);
    winnerText.setFillColor(Color::Yellow);
    winnerText.setPosition(Vector2f(220.f, 260.f));

    Text pauseText(font, "PAUSED", 55);
    pauseText.setFillColor(Color::Yellow);
    pauseText.setPosition(Vector2f(300.f, 240.f));

    RectangleShape middleLine(Vector2f(4.f, 600.f));
    middleLine.setPosition(Vector2f(448.f, 0.f));
    middleLine.setFillColor(Color(120, 120, 120));

    auto resetBall = [&]()
    {
        ball.setPosition(Vector2f(444.f, 294.f));
        ballSpeedX = -ballSpeedX;
        ballSpeedY = 4.f;
    };

    auto resetGame = [&]()
    {
        leftScore = 0;
        rightScore = 0;
        gameOver = false;
        paused = false;

        leftPaddle.setPosition(Vector2f(40.f, 240.f));
        rightPaddle.setPosition(Vector2f(840.f, 240.f));
        ball.setPosition(Vector2f(444.f, 294.f));

        ballSpeedX = 5.f;
        ballSpeedY = 4.f;
    };

    auto startSinglePlayer = [&]()
    {
        singlePlayer = true;
        menuScreen = false;
        modeText.setString("Mode: Single Player");
        resetGame();
    };

    auto startTwoPlayer = [&]()
    {
        singlePlayer = false;
        menuScreen = false;
        modeText.setString("Mode: Two Player");
        resetGame();
    };

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }

            if (menuScreen)
            {
                if (const auto* mouseButton = event->getIf<Event::MouseButtonPressed>())
                {
                    if (mouseButton->button == Mouse::Button::Left)
                    {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                        if (onePlayerText.getGlobalBounds().contains(mousePos))
                        {
                            startSinglePlayer();
                        }

                        if (twoPlayerText.getGlobalBounds().contains(mousePos))
                        {
                            startTwoPlayer();
                        }
                    }
                }
            }
        }

        if (menuScreen)
        {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (onePlayerText.getGlobalBounds().contains(mousePos))
                onePlayerText.setFillColor(Color::Cyan);
            else
                onePlayerText.setFillColor(Color::Yellow);

            if (twoPlayerText.getGlobalBounds().contains(mousePos))
                twoPlayerText.setFillColor(Color::Cyan);
            else
                twoPlayerText.setFillColor(Color::Yellow);

            window.clear(Color(20, 20, 60));
            window.draw(titleText);
            window.draw(onePlayerText);
            window.draw(twoPlayerText);
            window.display();

            continue;
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            menuScreen = true;
            resetGame();
            sleep(milliseconds(200));
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::R))
        {
            resetGame();
            sleep(milliseconds(200));
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::P))
        {
            paused = !paused;
            sleep(milliseconds(200));
        }

        if (!gameOver && !paused)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::W) && leftPaddle.getPosition().y > 0)
            {
                leftPaddle.move(Vector2f(0.f, -paddleSpeed));
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::S) &&
                leftPaddle.getPosition().y + leftPaddle.getSize().y < HEIGHT)
            {
                leftPaddle.move(Vector2f(0.f, paddleSpeed));
            }

            if (singlePlayer)
            {
                float rightPaddleCenter =
                    rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f;

                float ballCenter =
                    ball.getPosition().y + ball.getRadius();

                if (rightPaddleCenter < ballCenter - 15 &&
                    rightPaddle.getPosition().y + rightPaddle.getSize().y < HEIGHT)
                {
                    rightPaddle.move(Vector2f(0.f, aiSpeed));
                }

                if (rightPaddleCenter > ballCenter + 15 &&
                    rightPaddle.getPosition().y > 0)
                {
                    rightPaddle.move(Vector2f(0.f, -aiSpeed));
                }
            }
            else
            {
                if (Keyboard::isKeyPressed(Keyboard::Key::Up) &&
                    rightPaddle.getPosition().y > 0)
                {
                    rightPaddle.move(Vector2f(0.f, -paddleSpeed));
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::Down) &&
                    rightPaddle.getPosition().y + rightPaddle.getSize().y < HEIGHT)
                {
                    rightPaddle.move(Vector2f(0.f, paddleSpeed));
                }
            }

            ball.move(Vector2f(ballSpeedX, ballSpeedY));

            if (ball.getPosition().y <= 0 ||
                ball.getPosition().y + ball.getRadius() * 2 >= HEIGHT)
            {
                ballSpeedY = -ballSpeedY;
            }

            if (ball.getGlobalBounds().findIntersection(leftPaddle.getGlobalBounds()).has_value())
            {
                ballSpeedX = std::abs(ballSpeedX);
                ballSpeedX *= 1.05f;

                float paddleCenter =
                    leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.f;

                float ballCenter =
                    ball.getPosition().y + ball.getRadius();

                ballSpeedY = (ballCenter - paddleCenter) / 15.f;
            }

            if (ball.getGlobalBounds().findIntersection(rightPaddle.getGlobalBounds()).has_value())
            {
                ballSpeedX = -std::abs(ballSpeedX);
                ballSpeedX *= 1.05f;

                float paddleCenter =
                    rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f;

                float ballCenter =
                    ball.getPosition().y + ball.getRadius();

                ballSpeedY = (ballCenter - paddleCenter) / 15.f;
            }

            if (ball.getPosition().x < 0)
            {
                rightScore++;
                resetBall();
            }

            if (ball.getPosition().x > WIDTH)
            {
                leftScore++;
                resetBall();
            }

            if (leftScore >= WINNING_SCORE)
            {
                winnerText.setString("Sol Oyuncu Kazandi!");
                gameOver = true;
            }

            if (rightScore >= WINNING_SCORE)
            {
                winnerText.setString("Sag Oyuncu Kazandi!");
                gameOver = true;
            }
        }

        scoreText.setString(std::to_string(leftScore) + "       " + std::to_string(rightScore));

        window.clear(Color(20, 20, 60));
        window.draw(middleLine);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(scoreText);
        window.draw(infoText);
        window.draw(modeText);

        if (gameOver)
        {
            window.draw(winnerText);
        }

        if (paused)
        {
            window.draw(pauseText);
        }

        window.display();
    }

    return 0;
}