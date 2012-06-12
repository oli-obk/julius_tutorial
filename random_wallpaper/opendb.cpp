
#include <exception>

sqlite3* opendb(std::string path)
{
	//sqlite3-zeiger
	sqlite3*	Database;

	if(sqlite3_open(Path.c_str(), &Database) != SQLITE_OK)
	{
		cout << "Fehler beim Oeffnen: " << sqlite3_errmsg(Database) << endl;
		throw std::runtime_error("konnte datenbank nicht öffnen");
	}	
	return Database;
}
