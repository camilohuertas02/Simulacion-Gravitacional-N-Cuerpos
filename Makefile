# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -lm

# Directorios
SRCDIR = src
INCLUDEDIR = include
BINDIR = bin
DOCDIR = documents
RESULTSDIR = results
TESTDIR = test

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES = $(TESTDIR)/testing.cpp
TEST_MAIN = $(TESTDIR)/main_test.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_MAIN_OBJ = $(TEST_MAIN:.cpp=.o)

# Ejecutables
EXECUTABLE = gravedad
TEST_EXECUTABLE = $(TESTDIR)/test_graficas

# Archivo LaTeX principal y PDF
LATEX_DOC = $(DOCDIR)/gravitacional.tex
PDF_DOC = $(DOCDIR)/gravitacional.pdf

# Archivo Doxyfile y directorio de salida HTML de Doxygen
DOXYFILE = $(DOCDIR)/Doxyfile
DOXY_OUTPUT_HTML = $(DOCDIR)/html
DOXY_OUTPUT_LATEX = $(DOCDIR)/latex

# --- Reglas Principales ---

# Regla por defecto: compilar solo el programa principal
all: $(BINDIR)/$(EXECUTABLE)

# Compilación del ejecutable principal (SIN archivos de test)
$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $(BINDIR)/$(EXECUTABLE) $(LDFLAGS)
	@echo "Compilación exitosa: $(BINDIR)/$(EXECUTABLE)"

# Compilación del ejecutable de testing (en test/)
$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(TEST_MAIN_OBJ)
	$(CXX) $(TEST_OBJECTS) $(TEST_MAIN_OBJ) -o $(TEST_EXECUTABLE) $(LDFLAGS)
	@echo "Compilación de testing exitosa: $(TEST_EXECUTABLE)"

# Dependencias específicas para cada archivo objeto
$(SRCDIR)/main.o: $(SRCDIR)/main.cpp $(INCLUDEDIR)/vector3D.h $(INCLUDEDIR)/Cuerpo.h $(INCLUDEDIR)/utilidades.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o

$(SRCDIR)/Cuerpo.o: $(SRCDIR)/Cuerpo.cpp $(INCLUDEDIR)/Cuerpo.h $(INCLUDEDIR)/vector3D.h $(INCLUDEDIR)/utilidades.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Cuerpo.cpp -o $(SRCDIR)/Cuerpo.o

$(SRCDIR)/vector3D.o: $(SRCDIR)/vector3D.cpp $(INCLUDEDIR)/vector3D.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/vector3D.cpp -o $(SRCDIR)/vector3D.o

$(SRCDIR)/utilidades.o: $(SRCDIR)/utilidades.cpp $(INCLUDEDIR)/utilidades.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/utilidades.cpp -o $(SRCDIR)/utilidades.o

# Reglas para compilar archivos de testing
$(TESTDIR)/testing.o: $(TESTDIR)/testing.cpp $(TESTDIR)/testing.h
	$(CXX) $(CXXFLAGS) -c $(TESTDIR)/testing.cpp -o $(TESTDIR)/testing.o

$(TESTDIR)/main_test.o: $(TESTDIR)/main_test.cpp $(TESTDIR)/testing.h
	$(CXX) $(CXXFLAGS) -c $(TESTDIR)/main_test.cpp -o $(TESTDIR)/main_test.o

# Crear directorio bin si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

# --- Reglas de Documentación ---

# Generar documentación con Doxygen
dox: $(DOXYFILE)
	@echo "Generando documentación Doxygen..."
	cd $(DOCDIR) && doxygen Doxyfile
	@echo "Documentación Doxygen generada en $(DOXY_OUTPUT_HTML) y $(DOXY_OUTPUT_LATEX)."

# Compilar el documento LaTeX a PDF
pdf: $(LATEX_DOC)
	@echo "Generando PDF desde LaTeX..."
	cd $(DOCDIR) && pdflatex gravitacional.tex
	cd $(DOCDIR) && pdflatex gravitacional.tex # Segunda pasada para referencias
	@echo "PDF $(PDF_DOC) generado."

# --- Reglas de Prueba ---

# Regla para compilar y ejecutar el programa de testing
test: $(TEST_EXECUTABLE)
	@echo "Ejecutando programa de testing..."
	cd $(TESTDIR) && ./test_graficas

# Regla para solo compilar el programa de testing
test-build: $(TEST_EXECUTABLE)
	@echo "Programa de testing compilado: $(TEST_EXECUTABLE)"

# --- Reglas de Limpieza ---

clean:
	@echo "Limpiando archivos generados..."
	rm -f $(SRCDIR)/*.o
	rm -f $(TESTDIR)/*.o
	rm -f $(TESTDIR)/input_temp.txt
	rm -f $(BINDIR)/$(EXECUTABLE)
	rm -f $(TEST_EXECUTABLE)
	rm -rf $(DOXY_OUTPUT_HTML)
	rm -rf $(DOXY_OUTPUT_LATEX)
	rm -f $(DOCDIR)/*.aux $(DOCDIR)/*.log $(DOCDIR)/*.out $(DOCDIR)/*.toc $(DOCDIR)/*.pdf
	rm -f $(RESULTSDIR)/*.*
	rm
	@echo "Limpieza completada."

# Marcar reglas como phony (no son archivos)
.PHONY: all dox pdf clean test test-build
