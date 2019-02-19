	#include <pqxx/connection>
	#include <pqxx/transaction>
	#include <iostream>
	#include <string>
	#include <sstream>

	void help() {
	   std::cout << "Usage: <host> <user> <password> <database>" << std::endl;
	}

	int main(int argc, char **argv) {
	   // Check arguments
	   if (argc < 5) {
		   help();
		   return 1;
	   }

	   // Prepare connection string
	   std::ostringstream conn_string("");
	   
	   conn_string << "host=" << argv[1]
		   << " user=" << argv[2]
		   << " password=" << argv[3]
		   << " dbname=" << argv[4];

	   do {
		   // Create connection
		   try {
			   pqxx::connection conn(conn_string.str());
			   pqxx::work       xact(conn, "SampleSelect");

			   std::string      query("SELECT * from countries");
			   // Execute query
			   try {
				   pqxx::result res = xact.exec(query);
				   if (!res.size()) {
					   std::cout << "Empty result set." << std::endl;
					   break;
				   }
				   // Show results
				   for (pqxx::result::const_iterator i = res.begin(), r_end = res.end(); i != r_end; ++i) {
					   // Iterate fields
					   for (pqxx::result::const_fielditerator f = i->begin(), f_end = i->end(); f != f_end; ++f) {
						   std::cout << f->name() << " = '" << f->c_str() << "'" << std::endl;
					   }
					   std::cout << std::endl;
				   }
			   } catch (...) {
				   std::cout << "Failed to execute query: " << query << std::endl;
				   break;
			   }
		   } catch (pqxx::broken_connection) {
			   std::cout << "Failed to establish connection." << std::endl;
			   break;
		   }
		   std::cout << "Query successfully executed." << std::endl;

		   return 0;
	   } while (false);

	   return 1;
	}
