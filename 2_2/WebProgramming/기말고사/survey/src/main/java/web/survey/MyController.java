package web.survey;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.context.annotation.RequestScope;

import jakarta.servlet.http.HttpSession;


@Controller
public class MyController {
    @Autowired
    surveyRep srep;

    @GetMapping("/start")
    public String start() {
        return "start";
    }

    @GetMapping("/survey/1")
    public String survey1(HttpSession se, @RequestParam("userid") String userid) {
        se.setAttribute("userid", userid);

        return "survey1";
    }

    @GetMapping("/survey/2")
    public String survey2(HttpSession se, @RequestParam("artist") String artist) {
        se.setAttribute("artist", artist);

        return "survey2";
    }
    
    @GetMapping("/thanks")
    public String thanks(HttpSession se, @RequestParam("musician") String musician) {
        survey a = new survey();
        se.setAttribute("musician", musician);
        a.userid = (String)se.getAttribute("userid");
        a.artist = (String)se.getAttribute("artist");
        a.musician = musician;

        srep.save(a);
        
        return "thanks";
    }
    
    @GetMapping("/survey/result")
    public String result(HttpSession se, Model mo) {
        mo.addAttribute("userid", se.getAttribute("userid"));
        mo.addAttribute("artist", se.getAttribute("artist"));
        mo.addAttribute("musician", se.getAttribute("musician"));
        
        return "result";
    }

    @GetMapping("/survey/list")
    public String surveyList(Model mo) {
        mo.addAttribute("arr", srep.findAll());
        
        return "surveyList";
    }

    @GetMapping("/iam")
    public String iam() {
        return "iam";
    }

    @GetMapping("/iam/answer")
    public String iamAnswer(Model mo, @RequestParam("gender") String gender, @RequestParam("age") String age,
                           @RequestParam(name="foods", required=false) String[] foods, @RequestParam("handsome") int handsome,
                           @RequestParam("grade") int grade, @RequestParam("organized") int organized, @RequestParam("promote") String promote)
    {
        mo.addAttribute("gender", gender);
        mo.addAttribute("age", age);
        mo.addAttribute("foods", foods);
        mo.addAttribute("handsome", handsome);
        mo.addAttribute("grade", grade);
        mo.addAttribute("organized", organized);
        mo.addAttribute("promote", promote);

        return "iamAnswer";
    }
    
}