install(DIRECTORY erCv DESTINATION include 
                       COMPONENT Development 
		       REGEX  "/[^/]*.hpp~$" EXCLUDE
		       REGEX "/[^/]*toBind.hpp$" EXCLUDE
		       REGEX "/[^/]*.s$" EXCLUDE
		       REGEX ".svn" EXCLUDE
  )