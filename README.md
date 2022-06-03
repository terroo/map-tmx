# Map TMX
Parser example shown in the video described in this repository

---

### English
This repository does not have the images indicated in the `.tmx` file, you need to download them here at [this link](https://terminalroot.com/free-download-of-5-tileset-for-your-games/), unzip and save them in the `resources/tileset` directory of this repository .

That example described the details in [this video](https://youtu.be/jpyiN38_NPY). Watch if you can't get this example to work
> The path of the images can be identified by reading the file [file.tmx](https://github.com/terroo/map-tmx/blob/main/file.tmx)

```sh
cat file.tmx
```

---

### Português
Esse repositório não tem as imagens indicadas no arquivo `.tmx` , você precisa fazer o download delas aqui [nesse link](https://terminalroot.com.br/2022/04/baixe-de-graca-5-tilesets-para-seus-games.html) , descompactar e salvar dentro do diretório `resources/tileset` desse repositório.

Esse exemplo descrito os detalhes [nesse vídeo](https://youtu.be/jpyiN38_NPY). Assista caso não esteja conseguindo fazer funcionar esse exemplo
> O caminho das imagens pode ser identificado lendo o arquivo [file.tmx](https://github.com/terroo/map-tmx/blob/main/file.tmx)

```sh
cat file.tmx
```

# Dependencies
+ [SFML](https://github.com/SFML/SFML)
+ [TinyXML2](https://github.com/leethomason/tinyxml2)
+ [g++](https://github.com/gcc-mirror/gcc)
+ [GNU Make](https://savannah.gnu.org/git/?group=make)

---

# Building

```sh
git clone https://github.com/terroo/map-tmx
cd map-tmx
make
```


