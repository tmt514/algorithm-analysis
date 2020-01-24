if (window.MathJax === undefined) {
  window.MathJax = {
    TeX: {
      Macros: {
        E: "\\mathbb{E}",
        Inv: "\\mathrm{Inv}",
        floor: ["\\left\\lfloor{#1}\\right\\rfloor", 1],
        ceil: ["\\left\\lceil{#1}\\right\\rceil", 1]
      }
    }
  };
} else {
  
  window.MathJax.Hub.Config({
    TeX: {
      Macros: {
        E: "\\mathbb{E}",
        Inv: "\\mathrm{Inv}",
        floor: ["\\left\\lfloor{#1}\\right\\rfloor", 1],
        ceil: ["\\left\\lceil{#1}\\right\\rceil", 1]
      }
    }    
  });
  
  // window.MathJax.InputJax.TeX.Macro('E', "\\mathbb{E}");
  // window.MathJax.InputJax.TeX.Macro('Inv', "\\mathrm{Inv}");
  // window.MathJax.InputJax.TeX.Macro('floor',"\\left\\lfloor{#1}\\right\\rfloor", 1);
  // window.MathJax.InputJax.TeX.Macro('ceil', "\\left\\lceil{#1}\\right\\rceil", 1);
}

