import matplotlib.pyplot as plt
import yfinance as yf
import sys

if len(sys.argv) < 2:
    print("Błąd: Nie podano symbolu akcji.")
    sys.exit(1)

symbol = sys.argv[1]  # np. "AAPL"
stock = yf.Ticker(symbol)
hist = stock.history(period="7d")

plt.figure(figsize=(7, 4))  # szerszy i wyższy
plt.plot(hist.index, hist['Close'], label=symbol)
plt.title(f"Kurs {symbol} (7 dni)")
plt.xlabel("Dzień")
plt.ylabel("Cena")
plt.grid(True)
plt.tight_layout()
plt.savefig("wykres.png")
