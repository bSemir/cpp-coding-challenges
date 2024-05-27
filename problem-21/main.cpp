#include <iostream>
#include <string>

struct Song {
    Song(const char string[15], const char string1[11], int i) {
        title = string;
        artist = string1;
        duration = i;
    }
    std::string title;
    std::string artist;
    int duration;
};

class Playlist {
public:
    Playlist();
    Playlist(const Playlist& other);
    Playlist(Playlist&& other);
    Playlist& operator=(const Playlist& other);
    Playlist& operator=(Playlist&& other);
    ~Playlist() { dealociraj(); }
    void add_song(const Song& song);
    void print_playlist() const;
private:
    Song** songs;
    int capacity;
    int length;
    void dealociraj();
};

void Playlist::print_playlist() const {
    for (int i = 0; i < length; ++i) {
        std::cout << "Title: " << songs[i]->title << ", Artist: " << songs[i]->artist
                  << ", Duration: " << songs[i]->duration << " seconds" << std::endl;
    }
}

void Playlist::dealociraj() {
    for (int i = 0; i < length; i++) delete songs[i];
    delete[] songs;
}

Playlist::Playlist() : songs(new Song*[10] {}), capacity(10), length(0) {}

// copy constructor
Playlist::Playlist(const Playlist &other) : songs(new Song*[other.capacity] {}), capacity(other.capacity), length(other.length) {
    try {
        for (int i = 0; i < length; i++) {
            songs[i] = new Song(*other.songs[i]);
        }
    } catch (...) {
        dealociraj();
        throw;
    }
}

// move constructor
Playlist::Playlist(Playlist &&other) : songs(other.songs), capacity(other.capacity), length(other.length) {
    other.songs = nullptr;
    other.capacity = 0;
    other.length = 0;
}

// copy assignment operator
Playlist& Playlist::operator=(const Playlist &other) {
    if (this == &other) return *this;
    dealociraj(); // hmmm
    songs = new Song*[other.capacity] {};
    capacity = other.capacity;
    length = other.length;
    try {
        for (int i = 0; i < length; i++) songs[i] = new Song(*other.songs[i]);
    } catch (...) {
        dealociraj();
        throw;
    }
    return *this;
}

// move assignment operator
Playlist& Playlist::operator=(Playlist &&other) {
    if (this == &other) return *this;
    std::swap(songs, other.songs);
    std::swap(capacity, other.capacity);
    return *this;
}

void Playlist::add_song(const Song &song) {
    if (length == capacity) {
        std::cout << "Playlist is full, cannot add another song." << std::endl;
        return;
    }
    // add new song to the array
    songs[length] = new Song(song);
    length++;
}

int main() {
    // Creating some songs
    Song song1("Song One", "Artist One", 210);
    Song song2("Song Two", "Artist Two", 180);
    Song song3("Song Three", "Artist Three", 240);


    // Testing default constructor and add_song

    Playlist playlist1 = Playlist();
    playlist1.add_song(song1);
    playlist1.add_song(song2);
    std::cout << "Playlist 1 after adding songs:" << std::endl;
    playlist1.print_playlist();

    // Testing copy constructor
    Playlist playlist2(playlist1);
    std::cout << "\nPlaylist 2 (copy of Playlist 1):" << std::endl;
    playlist2.print_playlist();

    // Testing move constructor
    Playlist playlist3(std::move(playlist1));
    std::cout << "\nPlaylist 3 (moved from Playlist 1):" << std::endl;
    playlist3.print_playlist();

    // Testing copy assignment operator
    Playlist playlist4;
    playlist4 = playlist2;
    std::cout << "\nPlaylist 4 (assigned from Playlist 2):" << std::endl;
    playlist4.print_playlist();

    // Testing move assignment operator
    Playlist playlist5;
    playlist5 = std::move(playlist3);
    std::cout << "\nPlaylist 5 (moved from Playlist 3):" << std::endl;
    playlist5.print_playlist();

    // Testing self-assignment
    playlist5 = playlist5;
    std::cout << "\nPlaylist 5 after self-assignment:" << std::endl;
    playlist5.print_playlist();

    // Testing remove_song and get_song
    playlist5.add_song(song3);
    std::cout << "\nPlaylist 5 after adding another song:" << std::endl;
    playlist5.print_playlist();

    return 0;
}