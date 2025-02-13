<<<<<<< HEAD
package web.chap05;

import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class AirController {
    @Autowired
    private memberRep mrep;

    @GetMapping("/member/list")
    public String memberList(Model mo) {
        List<member> arr = mrep.findAll();
        mo.addAttribute("arr", arr);
        return "memberList";
    }

    @GetMapping("/member/new")
    public String memberNew() {
        return "memberNew";
    }

    @GetMapping("/member/insert")
    public String memberInsert(@RequestParam("mid") String mid, @RequestParam("pw") String pw,
            @RequestParam("name") String name, @RequestParam("phone") String phone, Model mo) {
        if (mrep.existsById(mid)) {
            mo.addAttribute("msg", mid + "는이미사용되고있는아이디입니다.");
            mo.addAttribute("url", "back");
        }
        
        else {
            member obj = new member();
            obj.mid = mid;
            obj.pw = pw;
            obj.name = name;
            obj.phone = phone;
            obj.mileage = 1000;

            mrep.save(obj);
            mo.addAttribute("msg", mid + "님, 반갑습니다!! (회원리스트로이동)");
            mo.addAttribute("url", "/member/list");
        }
        return "popup";
    }
}
=======
package web.chap05;

import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class AirController {
    @Autowired
    private memberRep mrep;

    @GetMapping("/memberList")
    public String memberList(Model mo) {
        List<member> arr = mrep.findAll();
        mo.addAttribute("arr", arr);
        return "memberList";
    }
} // class
>>>>>>> d43a0f184a790fc6e8be0be95e7ea59ceea6cf59
