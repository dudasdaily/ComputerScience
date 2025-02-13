package web.worldcup;

import java.time.LocalDateTime;

import org.hibernate.annotations.CreationTimestamp;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class member {
    @Id
    public String mid;
    public String pw;
    public String name;
    public String phone;
    public Integer mileage;
    @CreationTimestamp
    public LocalDateTime wdate;
}
