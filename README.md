## LowLevelManager
Program ma za zadanie ułatwienić inżynierie wsteczną procesów. 
Program pozwala automatycznie wykrywać parametry funkcji nie poddanych procesom zaciemniania kodu.

## Funkcjonalności:
* Podpinanie się pod proces.
* Deasemblacja procesu.
* Pobieranie podstawowych informacji o nim - architektura, adres początkowy, adres bazowy.
* Wstrzykiwanie kodu w postaci szesnastkowej oraz przy pomocy mnemonic assemblera - tworzenie wątków, alokacja pamięci oraz wstrzyknięcie.
* Wyszukiwanie po stringu, instrukcji oraz operandzie.
* Automatyczne rozpoznanie funkcji, wykrycie parametrów oraz typu wywołąnia. 
* Wywołanie funkcji z możliwością podania wartości parametrów.

## Technologie:
* C++
* C++/CLI
* Winforms

## Biblioteki:
* [ASMJIT][asmjit]
* [DISTORM][distorm]

## Poradnik:
```
Wywoływanie funkcji:
1. Zbuduj aplikacje.
2. Odpal aplikacje w trybie administratora.
3. Wybierz proces - OpenProcess.
4. Klinkij Recognize Function.
5. Podaj adres w postaci szesnastkowej. 
6. Kliknij recognize.
7. Wybierz call function.
8. Podaj parametry w rubryce value.
9. Wcisnij call function.
```


[asmjit]: https://github.com/asmjit/asmjit
[distorm]: https://github.com/gdabah/distorm
