
#include "okno.h"
#include "UserManager.h"


void window::initLoginPanelUI()
{
	
	// Czcionka musi być już załadowana!
	this->panelTitle.setFont(this->font);
	this->panelTitle.setCharacterSize(28);
	this->panelTitle.setString("Tryb: Logowanie");
	this->panelTitle.setFillColor(sf::Color::Black);

	sf::FloatRect titleBounds = this->panelTitle.getLocalBounds();
	this->panelTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
	this->panelTitle.setPosition(
		this->panel.getPosition().x + this->panel.getSize().x / 2,
		this->panel.getPosition().y + 20
	);

	// Login label
	this->loginLabel.setFont(this->font);
	this->loginLabel.setCharacterSize(20);
	this->loginLabel.setString("email:");
	this->loginLabel.setFillColor(sf::Color::Black);
	this->loginLabel.setPosition(
		this->panel.getPosition().x + 30,
		this->panel.getPosition().y + 70
	);

	// Hasło label
	this->passwordLabel.setFont(this->font);
	this->passwordLabel.setCharacterSize(20);
	this->passwordLabel.setString("Hasło:");
	this->passwordLabel.setFillColor(sf::Color::Black);
	this->passwordLabel.setPosition(
		this->panel.getPosition().x + 30,
		this->panel.getPosition().y + 120
	);

	// Login input text
	this->loginInputText.setFont(this->font);
	this->loginInputText.setCharacterSize(20);
	this->loginInputText.setFillColor(sf::Color::Black);
	this->loginInputText.setPosition(this->loginLabel.getPosition().x + 100, this->loginLabel.getPosition().y);

	// Password input text
	this->passwordInputText.setFont(this->font);
	this->passwordInputText.setCharacterSize(20);
	this->passwordInputText.setFillColor(sf::Color::Black);
	this->passwordInputText.setPosition(this->passwordLabel.getPosition().x + 100, this->passwordLabel.getPosition().y);

	// Przycisk zmiany trybu (logowanie <-> rejestracja)
	modeButton.setSize(sf::Vector2f(150, 40));
	modeButton.setFillColor(sf::Color::Green);
	modeButton.setOutlineColor(sf::Color::Black);
	modeButton.setOutlineThickness(2);

	// Pozycja np. na dole panelu
	modeButton.setPosition(
		panel.getPosition().x + panel.getSize().x / 2 - 75,
		panel.getPosition().y + panel.getSize().y - 60
	);

	// Tekst przycisku
	modeButtonText.setFont(font);
	modeButtonText.setCharacterSize(18);
	modeButtonText.setFillColor(sf::Color::Black);
	modeButtonText.setString("Zmień tryb");

	// Wyśrodkowanie tekstu w przycisku
	sf::FloatRect textBounds = modeButtonText.getLocalBounds();
	modeButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	modeButtonText.setPosition(
		modeButton.getPosition().x + modeButton.getSize().x / 2,
		modeButton.getPosition().y + modeButton.getSize().y / 2 - 5
	);

}


void window::initpanel()
{
	this ->panel.setSize(sf::Vector2f(400, 500));
	panel.setFillColor(sf::Color(128, 128, 128, 150));
	panel.setOutlineColor(sf::Color::Black);
	panel.setOutlineThickness(2);
	panel.setPosition(
		(this->okno->getSize().x - this->panel.getSize().x) / 2,
		(this->okno->getSize().y - this->panel.getSize().y) / 2
	);


}

/// @brief Ładuje teksturę tła z pliku
void window::initbacgrundtexture()
{
	if (!backgroundTexture.loadFromFile("resources/background.jpg")) {
		std::cout << "nieda sie zaladowac obraska" << std::endl;
	}
}

/// @brief Inicjalizuje zmienne klasy (ustawia wskaźniki na nullptr)
void window::initialiseVariable()
{
	this->zalogowano = false;
	this->okno = nullptr;
}

/// @brief Tworzy główne okno aplikacji i ustawia jego parametry
void window::initWindow()
{
	this->VideoMode.width = 1500;
	this->VideoMode.height = 900;
	this->okno = new sf::RenderWindow(this->VideoMode, "aplikacja gieldowa",
		sf::Style::Titlebar | sf::Style::Close);
	this->okno->setFramerateLimit(60);
}


/// @brief Inicjalizuje tekst wyświetlany na ekranie
void window::intttext()
{
	this->uitext.setFont(this->font);
	this->uitext.setCharacterSize(32);
	this->uitext.setFillColor(sf::Color::White);

	
}

/// @brief Ładuje czcionkę z pliku
void window::init_font()
{
	if (!this->font.loadFromFile("resources/sansation.ttf")) {
		std::cout << "ladowanie sie nie powiodł" << std::endl;
	}
}

/// @brief Ustawia sprite tła i dopasowuje jego rozmiar do wielkości okna
void window::inittexturerender()
{
	this->backgroundSprite.setTexture(backgroundTexture);

	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = this->okno->getSize();

	if (textureSize.x == 0 || textureSize.y == 0) {
		std::cout << "Błąd: rozmiar tekstury to 0x0 – nie skaluję." << std::endl;
		return;
	}

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	this->backgroundSprite.setScale(scaleX, scaleY);
}

void window::renderPortfolioUI()
{
	if (portfolioNeedsRefresh) {
		portfolio.loadFromFile(currentUser);  // załaduj na nowo dane
		portfolioNeedsRefresh = false;
	}

	float windowWidth = this->okno->getSize().x;   // lub jaka faktycznie jest szerokość Twojego okna
	float windowHeight = this->okno->getSize().y;


	sf::RectangleShape panel;
	panel.setSize(sf::Vector2f(windowWidth - 40.f, 200.f));
	panel.setFillColor(sf::Color(230, 230, 230)); // jasnoszare tło
	panel.setOutlineColor(sf::Color(150, 150, 150));
	panel.setOutlineThickness(2.f);
	panel.setPosition(20.f, windowHeight - 220.f); // przyklejone do dołu

	this->okno->draw(panel);

	float x = 30.f;
	float y = windowHeight - 210.f;
	float rowHeight = 24.f;

	sf::Text header("POZYCJA	|	ILOSC	|	SR. CENA	|	CENA RYNKOWA	|	WARTOSC		|	ZYSK %", font, 14);
	header.setPosition(x, y);
	header.setFillColor(sf::Color::Black);
	this->okno->draw(header);
	y += rowHeight;

	for (const auto& entry : portfolio.getEntries()) {
		std::string ticker = entry.ticker;
		int qty = entry.quantity;
		float avg = entry.avgBuyPrice;
		float marketPrice = market.getPriceForSymbol(ticker);
		float total = marketPrice * qty;
		float change = (marketPrice - avg) / avg * 100;


		std::ostringstream ss;
		ss.precision(2);
		ss << std::fixed;
		ss << ticker << " | " << qty << " | " << avg << " | " << marketPrice << " | " << total << " | " << change << "%";

		sf::Text line(ss.str(), font, 14);
		line.setPosition(x, y);
		line.setFillColor(sf::Color::Black);
		this->okno->draw(line);

		y += rowHeight;
	}
	// suma portfela
	float totalPortfolioValue = 0.f;
	for (const auto& entry : portfolio.getEntries()) {
		float marketPrice = market.getPriceForSymbol(entry.ticker);
		totalPortfolioValue += marketPrice * entry.quantity;
	}
/*
	//// Wartość całego portfela
	//sf::Text totalText("Wartość portfela: " + std::to_string(static_cast<int>(totalPortfolioValue)) + " PLN", font, 16);
	//totalText.setPosition(x, y + 10.f);
	//totalText.setFillColor(sf::Color::Blue);
	//this->okno->draw(totalText);

	//// Saldo gotówki
	//sf::Text cashText("Saldo: " + std::to_string(static_cast<int>(portfolio.getCash())) + " PLN", font, 16);
	//cashText.setPosition(x, y + 34.f);
	//cashText.setFillColor(sf::Color::Black);
	//this->okno->draw(cashText);*/

}


//dotyczy wądków 
void window::startUpdateThread() {
	running1 = true;

	updateThread = std::thread([this] {
		while (running1.load()) {
			std::this_thread::sleep_for(std::chrono::seconds(30));
			if (!running1.load()) break;

			std::cout << "[WĄTEK] Aktualizacja akcji...\n";
			market.update();
		}
		});

}



/// @brief Konstruktor klasy window – inicjalizuje wszystkie elementy okna
window::window() : userManager("users.txt"), 
xd("Aplikacja giełdowa autorstwa Adama Taborka!","resources/sansation.ttf", 14) // <-- dodane tu
{

	this->initialiseVariable();
	this->initWindow();
	this->init_font();
	this->initbacgrundtexture();
	this->inittexturerender();
	this->intttext();
	this->initpanel();
	this->initLoginPanelUI();
}

/// @brief Destruktor klasy window – zwalnia pamięć
window::~window()
{
	running1 = false;
	if (updateThread.joinable()) {
		updateThread.join();
	}
	if (wykresThread.joinable()) {
		wykresThread.join();
	}


	delete this->okno;
}

/// @brief Sprawdza, czy okno aplikacji nadal działa (jest otwarte)
/// @return true jeśli okno jest otwarte, false jeśli zamknięte
const bool window::running() const
{
	return this->okno->isOpen();
}

void window::handleTextInput(const sf::Event& e)
{
	if (e.text.unicode < 128)
	{
		char entered = static_cast<char>(e.text.unicode);

		if (entered == '\b') { // backspace
			if (writingLogin && !loginBuffer.empty())
				loginBuffer.pop_back();
			else if (!writingLogin && !passwordBuffer.empty())
				passwordBuffer.pop_back();
		}
		else if (entered == '\r') { // Enter
			if (writingLogin)
				writingLogin = false;
			else {
				processLoginOrRegister();   // wywołaj logikę
				writingLogin = true;        // wróć do loginu
				loginBuffer.clear();
				passwordBuffer.clear();
			}
		}
		else if (std::isprint(static_cast<unsigned char>(entered))) {
			if (writingLogin)
				loginBuffer += entered;
			else
				passwordBuffer += entered;
		}

		// aktualizuj tekst
		loginInputText.setString(loginBuffer);
		passwordInputText.setString(std::string(passwordBuffer.length(), '*'));
	}
}

void window::processLoginOrRegister()
{
	if (mode == LOGIN)
	{
		if (userManager.validateLogin(loginBuffer, passwordBuffer)) {

			xd.draw(*this->okno);
			market.loadStocks();
			market.update();
			startUpdateThread();     // <-- uruchomienie osobnego wątku
			currentUser = loginBuffer;
			portfolio.loadFromFile(currentUser);
			
			mode = MARKET_VIEW;
		}



		else {
			this->panelTitle.setString("Błędny login lub hasło.");

		}
	}
	else if (mode == REGISTER)
	{
		if (!userManager.isValidEmail(loginBuffer)) {
			this->panelTitle.setString("Podaj prawidłowy adres e-mail.");
		}
		else if (userManager.userExists(loginBuffer)) {
			this->panelTitle.setString("Użytkownik już istnieje!");
		}
		else {
			userManager.registerUser(loginBuffer, passwordBuffer);
			this->panelTitle.setString("Rejestracja zakończona!");
		}
	}
}


void window::panelrysowanie(sf::RenderTarget& target)
{
	target.draw(panel);                // Tło panelu
	target.draw(panelTitle);          // Tytuł

	target.draw(loginLabel);          // "Login:"
	target.draw(loginInputText);      // Pole loginu

	target.draw(passwordLabel);       // "Hasło:"
	target.draw(passwordInputText);   // Pole hasła

	target.draw(modeButton);
	target.draw(modeButtonText);

}

void window::pollEvent()
{
	while (this->okno->pollEvent(this->wydarzenie))
	{
		switch (this->wydarzenie.type)
		{
		case sf::Event::Closed:
			this->okno->close();
			break;

		case sf::Event::TextEntered:
			this->handleTextInput(this->wydarzenie);
			break;

		case sf::Event::MouseButtonPressed:
		{
			if (wydarzenie.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = sf::Vector2f(
					static_cast<float>(wydarzenie.mouseButton.x),
					static_cast<float>(wydarzenie.mouseButton.y)
				);

				if (modeButton.getGlobalBounds().contains(mousePos)) {
					// Zmień tryb
					mode = (mode == LOGIN ? REGISTER : LOGIN);

					// Zmień tytułpanelu
					 this->panelTitle.setString(mode == LOGIN ? "Tryb: Logowanie" : "Tryb: Rejestracja");
					// Zmień tekst na przycisku
					modeButtonText.setString(mode == LOGIN ? "Rejestracja" : "Logowanie");

					// Wycentruj nowy tekst w przycisku
					sf::FloatRect textBounds = modeButtonText.getLocalBounds();
					modeButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
					modeButtonText.setPosition(
						modeButton.getPosition().x + modeButton.getSize().x / 2,
						modeButton.getPosition().y + modeButton.getSize().y / 2 - 5
					);
				}

			}
			if (mode == MARKET_VIEW && wydarzenie.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f clickPos(
					static_cast<float>(wydarzenie.mouseButton.x),
					static_cast<float>(wydarzenie.mouseButton.y) + scrollY  // dodaj scroll
				);

				auto akcje = market.getStocksSortedBySymbol();

				size_t maxIndex = std::min(visibleStockIndex + stocksPerPage, akcje.size());
				float lineSpacing = 600.f / static_cast<float>(stocksPerPage); // tak jak w renderze

				for (size_t i = visibleStockIndex; i < maxIndex; ++i) {
					const Stock& stock = akcje[i];
					float y = 30.f + (i - visibleStockIndex) * lineSpacing;

					// Prostokąt obszaru jednej akcji
					sf::FloatRect akcjaRect(30.f, y - scrollY, 400.f, lineSpacing);

					if (akcjaRect.contains(clickPos)) {
						// Tylko jeśli kliknięto inną akcję niż ostatnio
						if (stock.getSymbol() != selectedSymbol) {
							selectedSymbol = stock.getSymbol();

							if (wykresThread.joinable())
								wykresThread.join();

							std::string cmd = "python plot.py " + selectedSymbol;
							std::system(cmd.c_str());

							wykresThread = std::thread(&window::generujIWczytajWykres, this, selectedSymbol);
						}

						break;
					}

				}
				sf::Vector2f pos(wydarzenie.mouseButton.x, wydarzenie.mouseButton.y);
				if (logout && logout->handleClick(pos)) {
					currentUser.clear();
					mode = LOGIN;
					logout.reset(); // wyczyść logout button

				}

				// --- Przyciski Kup/Sprzedaj ---
				if (!selectedSymbol.empty()) {
					if (lastBuyRect.contains(clickPos)) {
						float price = market.getPriceForSymbol(selectedSymbol);
						portfolio.buyStock(selectedSymbol, price, 1);
						portfolio.saveToFile(currentUser);
						portfolioNeedsRefresh = true;

					}
					else if (lastSellRect.contains(clickPos)) {
						float price = market.getPriceForSymbol(selectedSymbol);
						portfolio.sellStock(selectedSymbol, price, 1);
						portfolio.saveToFile(currentUser);
						portfolioNeedsRefresh = true;

					}
				}
			}

			break;
		}
		case sf::Event::MouseWheelScrolled:
			if (wydarzenie.mouseWheelScroll.delta < 0) {
				// scroll w dół
				if (visibleStockIndex + stocksPerPage < market.getStocksSortedBySymbol().size())
					visibleStockIndex += stocksPerPage;
			}
			else if (wydarzenie.mouseWheelScroll.delta > 0) {
				// scroll w górę
				if (visibleStockIndex >= stocksPerPage)
					visibleStockIndex -= stocksPerPage;
			}
			break;



		}
	}
}

/// @brief Renderuje tło w oknie
void window::renderowanietła()
{
	this->okno->draw(backgroundSprite);
	 xd.draw(*this->okno);

}

void window::okno_update()
{
	this->pollEvent();  // zawsze odczytaj zdarzenia

	
}

/// @brief Główna funkcja rysująca – czyści, rysuje elementy i wyświetla
void window::okno_render()
{
	if (mode == MARKET_VIEW){
		this->okno->clear(sf::Color::White); // białe tło po zalogowaniu
		logout = std::make_unique<StandardLogoutButton>(font, 1350, 10.f);
		// np. prawy górny róg
}
	else {
		this->okno->clear(sf::Color::Magenta);
		this->renderowanietła(); // tylko w trybie logowania
	}

	if (mode == LOGIN || mode == REGISTER)
		this->panelrysowanie(*this->okno);
	else if (mode == MARKET_VIEW) {
		this->renderMarketUI(*this->okno);
		if (logout) logout->render(*okno);


	}

	this->okno->display();
}
void window::generujIWczytajWykres(const std::string& symbol) {
	if (symbol.empty()) {
		std::cout << "[WĄTEK] Błąd: symbol jest pusty — nie uruchamiam plot.py\n";
		return;
	}
	std::string cmd = "python plot.py " + symbol;
	std::system(cmd.c_str());  // tylko generowanie obrazu w tle
	// Sygnał dla głównego wątku: obraz gotowy do załadowania
	std::cout << "[WĄTEK] Uruchamiam: " << cmd << std::endl;

	
		std::lock_guard<std::mutex> lock(wykresMutex);
		this->wykresGotowy = true;
	
}

// Fragment renderMarketUI z ramką i przewijaniem
void window::renderMarketUI(sf::RenderTarget& target)
{
	// ====== 1. RenderTexture jako bufor ramki ======
	sf::RenderTexture contentTexture;
	contentTexture.create(400, 600); // rozmiar taki jak ramki
	contentTexture.clear(sf::Color::White); // tło białe

	auto akcje = market.getStocksSortedBySymbol();
	size_t maxIndex = std::min(visibleStockIndex + stocksPerPage, akcje.size());

	float ramkaHeight = 600.f;
	float lineSpacing = ramkaHeight / static_cast<float>(stocksPerPage); // np. 60px przy 10 akcjach

	for (size_t i = visibleStockIndex; i < maxIndex; ++i) {
		const Stock& stock = akcje[i];
		float y = 30.f + (i - visibleStockIndex) * lineSpacing;

		// === Rysowanie tekstu akcji ===
		float change = stock.getCurrentPrice() - stock.getPreviousPrice();
		float changePercent = (change / stock.getPreviousPrice()) * 100.0f;

		std::stringstream ss;
		ss << stock.getSymbol() << " - "
			<< stock.getCurrentPrice() << " PLN ("
			<< (change >= 0 ? "+" : "") << std::fixed << std::setprecision(2)
			<< changePercent << "%)";

		sf::Text textAkcji;
		textAkcji.setFont(this->font);
		textAkcji.setCharacterSize(18);
		textAkcji.setFillColor(sf::Color::Black);
		textAkcji.setPosition(10.f, y);
		textAkcji.setString(ss.str());
		contentTexture.draw(textAkcji);

		// === Jeśli kliknięto tę akcję – narysuj przyciski ===
		if (stock.getSymbol() == selectedSymbol) {
			if (this->wykresGotowy) {
				std::lock_guard<std::mutex> lock(wykresMutex);

				if (wykresTexture.loadFromFile("wykres.png")) {
					wykresSprite.setTexture(wykresTexture);
					wykresSprite.setPosition(460.f, 50.f);
					wykresSprite.setScale(1.5f, 1.5f);
					
				}
				this->wykresGotowy = false; // już załadowany
			}

			sf::RectangleShape buyButton(sf::Vector2f(80.f, 30.f));
			buyButton.setFillColor(sf::Color::Green);
			buyButton.setPosition(250.f, y); // dopasuj pozycję

			sf::Text buyText("Kup", font, 16);
			buyText.setPosition(260.f, y + 5.f);
			buyText.setFillColor(sf::Color::Black);

			sf::RectangleShape sellButton(sf::Vector2f(100.f, 30.f));
			sellButton.setFillColor(sf::Color::Red);
			sellButton.setPosition(335.f, y); // dopasuj pozycję

			sf::Text sellText("Sprzedaj", font, 16);
			sellText.setPosition(345.f, y + 5.f);
			sellText.setFillColor(sf::Color::Black);

			contentTexture.draw(buyButton);
			contentTexture.draw(buyText);
			contentTexture.draw(sellButton);
			contentTexture.draw(sellText);

			// Zapisz pozycje do kliknięcia
			lastBuyRect = buyButton.getGlobalBounds();
			lastBuyRect.top += 30.f - scrollY;
			lastBuyRect.left += 30.f;

			lastSellRect = sellButton.getGlobalBounds();
			lastSellRect.top += 30.f - scrollY;
			lastSellRect.left += 30.f;

		}
	}

	contentTexture.display();

	// ====== 2. Sprite z bufora i przesunięcie (scroll) ======
	sf::Sprite contentSprite(contentTexture.getTexture());
	contentSprite.setPosition(30.f, 30.f - scrollY); // RAMKA + scroll
	target.draw(contentSprite);

	// ====== 3. Ramka na wierzchu ======
	sf::RectangleShape frame;
	frame.setSize(sf::Vector2f(400.f, 600.f));
	frame.setFillColor(sf::Color::Transparent); // przezroczyste tło
	frame.setOutlineColor(sf::Color(100, 100, 100));
	frame.setOutlineThickness(4);
	frame.setPosition(30.f, 30.f);
	target.draw(frame);

	// ====== 4. Pasek przewijania ======
	sf::RectangleShape scrollbar;
	scrollbar.setSize(sf::Vector2f(8.f, 80.f));
	scrollbar.setFillColor(sf::Color(150, 150, 150));
	scrollbar.setPosition(430.f, 30.f + scrollY);
	target.draw(scrollbar);

	// <=== DODAJ TO:
	if (wykresSprite.getTexture()) {
		target.draw(wykresSprite);
	}
	sf::Text cashText;
	cashText.setFont(font);
	cashText.setCharacterSize(20);
	cashText.setFillColor(sf::Color::Black);
	cashText.setString("Saldo: " + std::to_string(static_cast<int>(portfolio.getCash())) + " PLN");
	cashText.setPosition(700.f, 10.f); // dopasuj do rozmiaru okna
	target.draw(cashText);


	renderPortfolioUI(); // <- na końcu
}
