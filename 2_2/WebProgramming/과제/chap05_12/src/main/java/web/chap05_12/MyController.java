package web.chap05_12;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class MyController {
    @Autowired
    private fruitsRep frep;

    @GetMapping("receipt")
    public String receipt(Model mo) {
        mo.addAttribute("arr", frep.findAll());

        return "receipt";
    }
}
