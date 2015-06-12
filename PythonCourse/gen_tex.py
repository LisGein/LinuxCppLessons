__author__ = 'lisgein'


def initial_data_begin_table():
    print("\\begin{center}")
    print("\\begin{tabular}{  | c | c | c | c | c | c | c | }")
    print("\\hline")
    print("Parameter & Value & Dimension & Index & Designation & Size & SI \\\\")
    print("\\hline")
    print("\\multicolumn{6}{|c}{Dimensions charge} & \\\\")
    print("\\hline")

def end_table():
    print("\\hline")
    print("\\end{tabular}")

def calc_data_begin_table():
        print("\\input{signature.tex}")
        print("\\begin{center}")
        print("\\textbf{\\textit{The calculated data}}\\\\")
        print("\\end{center}")

        print("\\begin{flushright}")
        print("\\textit{Table $N^o 3$: The calculated data}\\\\")
        print("\\end{flushright}")
        print("\\begin{tabular}{  | c | p{1.5cm} | p{1.5cm} | p{1.5cm} | c | c | p{1.5cm} | }")
        print("\\hline")

def dimensioning_begin_table():
        print("\\newpage")
        print("\\input{signature.tex}")
        print("\\begin{center}")
        print("\\textbf{\\textit{Dimensioning for quasi-stationary mode}}\\\\")
        print("\\end{center}")

        print("\\begin{flushright}")
        print("\\textit{Table $N^o 3$: The calculated data}\\\\")
        print("\\end{flushright}")
        print("\\tiny")
        print("\\renewcommand{\\arraystretch}{1} %% increase table row spacing")
        print("\\renewcommand{\\tabcolsep}{0.08cm}")
        print("\\begin{tabular}{|l*{18}{l|}}")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % (
        't', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)', '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)',
        '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")

def dimensioning_table():
        print("\\hline")
        print("\\end{tabular}\\\\")
        print("\\begin{tabular}{|l*{18}{l|}}")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % (
        't', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)', '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)',
        '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")

def begin_graphic(var):
    print("\\begin{tikzpicture}")
    print("\\begin{axis} [")
    print ("legend pos = outer north east,")
    print ("grid = major,")
    print ("height = 0.2\paperheight,")
    print ("width = 0.6\paperwidth ]")
    print '%s %s %s' % ('\\legend{ ', var, '};')

def prev_begin_graphic(var):
    print("\\begin{tikzpicture}")
    print("\\begin{axis} [")
    print ("legend pos = outer north east,")
    print ("height = 0.19\paperheight,")
    print ("width = 0.4\paperwidth ]")
    print '%s %s %s' % ('\\legend{ ', var, '};')
    print ("\\node[anchor=south west,inner sep=0] at (0,0) {\includegraphics[width=5.7cm, height=3.4cm]{fon.jpg}};")

def end_graphic():
    print("};")
    print("\\end{axis}")
    print("\\end{tikzpicture}")

def right_signature(str):
    print("\\begin{flushright}")
    print '%s %s %s \\\\' % ('\\textit{', str, '}')
    print("\\end{flushright}")

def begin_tableN4(time):
    print("\\begin{tabular}{|c|c|c|}")
    print("\\hline")
    print '%s & %s & %s  \\\\' % (' ', 'time', '$S_{gor svod}$')
    print("\\hline")
    print '%s & %d & %d  \\\\' % ('t', time, 0)
    print("\\hline")
    print '%s & %s & %s  \\\\' % ('x', 'y', '')

def table_building_profile_nozzle():
    print("\\newpage")
    print("\\input{signature.tex}")
    contents("Building a profile nozzle")
    print("\\begin{center}")

    print("\\begin{tabular}{|l*{16}{l|}}")
    print("\\hline")
    print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % (
        'i', 'li', '\(D_i\)', '\(F_i\)', '\(F_{kr}/F_i\)', '$\\lambda_i$', 'q($\\lambda_i$)', '$\\pi(\\lambda_i$)',
        '$\\tau(\\lambda_i$)', '$\\varepsilon(\\lambda_i$)', 'q($\\lambda_i) - F_{kr}/F_i$', 'P', 'T', '\(R_0\)', 'v')
    print("\\hline")

def add_section():
    print("\\addplot[dotted, mark = none, draw = brown, line width = 0.05 cm] coordinates { (1, 0.125) ")
    print("(1, -0.125)};")
    print("\\addplot[dotted, mark = none, draw = green, line width = 0.05 cm] coordinates { (1.5, 0.15) ")
    print("(1.5, -0.15)};")

def multicolumn():
    print("\\hline")
    print("\\multicolumn{6}{|c}{Data on fuel and combustion products} & \\\\")
    print("\\hline")

def contents(str):
    print("\\begin{center}")
    print("\\begin{large}")
    print '%s %s %s \\\\' % ('\\textbf{\\textit {', str, '}}')
    print("\\end{large}")
    print("\\end{center}")