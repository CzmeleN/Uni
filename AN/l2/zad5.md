# zad5

## katastrofa Ariane 5 (lot V88)

- zniszczony został ładunek czterech satelit, strata $370M
- rakieta zmieniła kierunek lotu 37 sekund po starcie
- było to spowodowane kodem, który miał miał części z Ariane 4, natomiast miał znacznie większe wartości prędkości, co spowodowało przepełnienie podczas konwersji 64-bitowego floatu na 16-bitowego inta
- int ten nie był chroniony przed przepełnieniem jak niektóre inne wartości, bo dane były z poprzedniego statku, a chcieli zaoszczędzić moc obliczeniową
- przepełnienie spowodowało wyjątek sprzętowy, mimo, że ten kod był zbędny po starcie, działał on nadal przez te prawie 40 sekund
- z założenia tylko jeden z modułów inercjii mógł się zepsuć, jednak przez to padły oba, a bit diagnostyczny został zinterpretowany przez komputer jako dane lotu
- przez to skręciły się w pełni dysze na boosterach oraz silnik Vulcain
- to spowodowało przechylenie o ponad 20 stopni, odłączenie boosterów i autodestrukcję launchera, a za tym całego lotu
