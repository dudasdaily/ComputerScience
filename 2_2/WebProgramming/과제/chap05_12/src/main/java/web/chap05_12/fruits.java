package web.chap05_12;

import org.hibernate.annotations.CreationTimestamp;
import java.time.LocalDateTime;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
public class fruits {
    @Id
    public int no;
    public String mid;
    public String fruit;
    public int quantities;
    @CreationTimestamp public LocalDateTime date;
}
