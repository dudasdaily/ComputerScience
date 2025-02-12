package web.surbey;

import java.time.LocalDateTime;

import org.hibernate.annotations.CreationTimestamp;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
public class survey {
    @Id
    public int no;
    public String id;
    public String color;
    public String os;
    @CreationTimestamp
    public LocalDateTime wdate;
}
