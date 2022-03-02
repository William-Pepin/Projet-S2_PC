//Implémentation Unix d'un driver primitif pour la manette du projet.
//La majorité du code vient de ChristophK sur StackOverflow.
//Voir: https://stackoverflow.com/questions/32522475/read-write-on-serial-device-dev-ttygs0-with-standard-c-fstream#35749399

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

class FilebufNoSeek : public std::filebuf
{
public:
    FilebufNoSeek() {};
protected:
    std::filebuf::pos_type _M_seek(std::filebuf::off_type __off, std::ios_base::seekdir __way, std::filebuf::__state_type __state);
    virtual std::filebuf::int_type overflow(std::filebuf::int_type __c);
};

std::filebuf::pos_type FilebufNoSeek::_M_seek(std::filebuf::off_type __off, std::ios_base::seekdir __way, std::filebuf::__state_type __state)
{
    pos_type __ret = pos_type(off_type(-1));
    if (_M_terminate_output())
    {
//      off_type __file_off = _M_file.seekoff(__off, __way); // Causes "illegal seek"
        off_type __file_off = off_type(0); // New - no seek
        if (__file_off != off_type(-1))
        {
            _M_reading = false;
            _M_writing = false;
            _M_ext_next = _M_ext_end = _M_ext_buf;
            _M_set_buffer(-1);
            _M_state_cur = __state;
            __ret = __file_off;
            __ret.state(_M_state_cur);
        }
    }
    return __ret;
}



std::filebuf::int_type FilebufNoSeek::overflow(std::filebuf::int_type __c)
{
    int_type __ret = traits_type::eof();
    const bool __testeof = traits_type::eq_int_type(__c, __ret);
    const bool __testout = (_M_mode & std::ios_base::out
            || _M_mode & std::ios_base::app);
    if (__testout)
    {
        if (_M_reading)
        {
            _M_destroy_pback();
            const int __gptr_off = _M_get_ext_pos(_M_state_last);
            if (_M_seek(__gptr_off, std::ios_base::cur, _M_state_last)
                    == pos_type(off_type(-1)))
                return __ret;
        }
        if (this->pbase() < this->pptr())
        {
            // If appropriate, append the overflow char.
            if (!__testeof)
            {
                *this->pptr() = traits_type::to_char_type(__c);
                this->pbump(1);
            }

            // Convert pending sequence to external representation,
            // and output.
            if (_M_convert_to_external(this->pbase(),
                    this->pptr() - this->pbase()))
            {
                _M_set_buffer(0);
                __ret = traits_type::not_eof(__c);
            }
        }
        else if (_M_buf_size > 1)
        {
            // Overflow in 'uncommitted' mode: set _M_writing, set
            // the buffer to the initial 'write' mode, and put __c
            // into the buffer.
            _M_set_buffer(0);
            _M_writing = true;
            if (!__testeof)
            {
                *this->pptr() = traits_type::to_char_type(__c);
                this->pbump(1);
            }
            __ret = traits_type::not_eof(__c);
        }
        else
        {
            // Unbuffered.
            char_type __conv = traits_type::to_char_type(__c);
            if (__testeof || _M_convert_to_external(&__conv, 1))
            {
                _M_writing = true;
                __ret = traits_type::not_eof(__c);
            }
        }
    }
    return __ret;
}


int main()
{
    int serial_port = open("/dev/ttyACM0", O_RDWR);


    struct termios tty;

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      return 1;
  }

    std::cout << "Ouverture du port tty..." << std::endl;
    FilebufNoSeek serialBuf;
    serialBuf.open("/dev/ttyACM0", std::ios_base::out | std::ios_base::in);


std::cout << "Écriture dans le port tty..." << std::endl;
std::iostream serialStream(&serialBuf);
serialStream << "test tty arduino" << std::endl;

std::this_thread::sleep_for(std::chrono::milliseconds(30));

std::cout << "Lecture du port tty..." << std::endl;
/*
int i=0;
int ssize = 0;
std::string retour;
while(i < 10000){
    //serialStream.sync();
    //serialStream.seekg(0, serialStream.beg);
    getline(serialStream,retour);
    //serialStream.seekg(0, serialStream.beg);
    //serialStream << std::endl;
    //ssize = serialStream.gcount();
    //retour[ssize] = '\0';
    std::cout << retour;
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    i++;
}
*/


    // get length of file:
int i=0;
while(i < 5000){
    serialStream.seekg (0, serialStream.end);
    int length = serialStream.tellg();
    serialStream.seekg (0, serialStream.beg);

    if(length != -1){
    char* buffer = new char [length+1];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    serialStream.read (buffer,length);

    buffer[length] = '\0';
    std::cout << buffer;
    delete[] buffer;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    i++;

}

    serialBuf.close();
    close(serial_port);

return 0;
}
