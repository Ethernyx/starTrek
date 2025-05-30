#include    "../include/object/Token.hh"                                

Token::Token(boost::json::object item) {
    this->_token = item.at("token").as_string().c_str();
    this->_key = item.at("key").as_string().c_str();
    this->_user = item.at("user").as_string().c_str();
}

Token::Token(const string key, const string user) : _key(key), _user(user) {
    _token = this->createJwt();
}

Token::~Token() {

}

string Token::base64UrlEncode(const string &str)
{

    const char base64_url_alphabet[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'};

    std::string out;
    int val = 0, valb = -6;
    size_t len = str.length();
    unsigned int i = 0;
    for (i = 0; i < len; i++) {
        unsigned char c = str[i];
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_url_alphabet[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        out.push_back(base64_url_alphabet[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    return out;
}

std::string Token::base64UrlDecode(const std::string & str) {
    const char base64_url_alphabet[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'};

  std::string out;
  std::vector<int> T(256, -1);
  unsigned int i;
  for (i =0; i < 64; i++) T[base64_url_alphabet[i]] = i;

  int val = 0, valb = -8;
  for (i = 0; i < str.length(); i++) {
    unsigned char c = str[i];
    if (T[c] == -1) break;
    val = (val<<6) + T[c];
    valb += 6;
    if (valb >= 0) {
      out.push_back(char((val>>valb)&0xFF));
      valb -= 8;
    }
  }
  return out;
}

string Token::createJwt() {
    // Créer l'en-tête
    boost::json::object header, payload;

    header["alg"] = "HS256";
    header["typ"] = "JWT";
    payload["iss"] = "admin";
    payload["sub"] = this->_user;
    payload["iat"] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    string encodedHeader = base64UrlEncode(boost::json::serialize(header));
    string encodedPayload = base64UrlEncode(boost::json::serialize(payload));

    // Créer la signature
    std::string signatureInput = encodedHeader + "." + encodedPayload;
    unsigned char* hmac = HMAC(EVP_sha256(), this->_key.c_str(), this->_key.length(),
                                (unsigned char*)signatureInput.c_str(), signatureInput.length(), NULL, NULL);
    std::string encodedSignature = base64UrlEncode(std::string((char*)hmac, EVP_MD_size(EVP_sha256())));

    // Retourner le token complet
    return encodedHeader + "." + encodedPayload + "." + encodedSignature;
}

string  Token::getToken() {
    return this->_token;
}

string  Token::getUser() {
    return this->_user;
}

boost::json::object         Token::generate(int id) {
    boost::json::object item;

    item["id"] = id;
    item["user"] = this->_user;
    item["key"] = this->_key;
    item["token"] = this->_token;
    return item;
}